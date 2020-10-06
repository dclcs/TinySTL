//
// Created by dcl on 2020/10/6.
//

#ifndef TINYSTL_HASH_H
#define TINYSTL_HASH_H
#include "../allocator/alloc.h"
#include "../iterator/iterator.h"
#include "vector.h"
#include "../algorithms/algobase.h"
namespace TinySTL{
    // Note: assumes long is at least 32 bits.
    static const int __stl_num_primes = 28;
    // SGI STL 提供 28 个质数，用质数大小来设计 buckets
    static const unsigned long __stl_prime_list[__stl_num_primes] =
            {
                    53ul,         97ul,         193ul,       389ul,       769ul,
                    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
                    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
                    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
                    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
                    1610612741ul, 3221225473ul, 4294967291ul
            };
    inline unsigned long __stl_next_prime(unsigned long n){
        const unsigned long* first = __stl_prime_list;
        const unsigned long* last = __stl_prime_list + __stl_num_primes;
        const unsigned long* pos = lower_bound(first, last, n);//lower_bound

        return pos == last ? *(last - 1) : *pos;
    }



    //hash node
    template <class Value>
    struct __hashtable_node{
        __hashtable_node* next;
        Value val;
    };

    /**
     *
     * @tparam Value : node value
     * @tparam Key : node key
     * @tparam HashFcn : hash function type
     * @tparam ExtractKey : get key from node(function or affine function)
     * @tparam EqualKey: is two key is equal(function or affine function)
     * @tparam Alloc
     */
    template <class Value, class Key, class HashFcn,
            class ExtractKey, class EqualKey, class Alloc = MyAlloc>
    class hashtable{
    public:
        typedef HashFcn hasher;
        typedef EqualKey key_equal;
        typedef size_t size_type;
        typedef Value value_type;


    private:
        hasher hash;
        key_equal equals;
        ExtractKey get_key;

        typedef __hashtable_node<Value> node;
        typedef simple_alloc<node, Alloc> node_allocator;


        node* new_node(const value_type& obj){
            node* n = node_allocator::allocate();
            n->next = 0;
            construct(&n->val, obj);
            return n;
        }

        void delete_node(node* n){
            destory(&n->val);
            node_allocator::deallocate();
        }

        vector<node*, Alloc> buckets;
        size_type num_elements;

    public:
        hashtable(size_type n,
                  const HashFcn& hf,
                  const EqualKey& eql): hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0){
            initialize_buckets(n);
        }

        void initialize_buckets(size_type n){
            const size_type n_buckets = next_size(n);
            buckets.reserve(n_buckets);
            buckets.insert(buckets.end(), n_buckets, (node*) 0);
            num_elements = 0;
        }

        //TODO : TEST hashtable.resize()

        void resize(size_type num_elements_hint);
        size_type next_size(size_type n) const {
            return __stl_next_prime(n);
        }
        size_type bucket_count() const {return buckets.size();}

        size_type max_bucket_count() const {
            return __stl_prime_list[__stl_num_primes - 1];
        }
    };



    //hash iterator
    template <class Value, class Key, class HashFcn,
            class ExtractKey, class EqualKey, class Alloc>
    struct __hashtable_iterator{
        typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
        typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
        typedef __hashtable_node<Value> node;

        typedef forward_iterator_tag iterator_category;
        typedef Value value_type;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef Value& reference;
        typedef Value* pointer;

        node *cur;
        hashtable *ht;

        __hashtable_iterator(node* n, hashtable* tab) : cur(n), ht(tab) {}
        __hashtable_iterator() {}
        reference operator*() const {return cur->val;}
        pointer operator->() const  {return &(operator*());}
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& it) const {return cur == it.cur;}
        bool operator!=(const iterator& it) const {return cur != it.cur;}
    };


}//end namespace

#include "hash_impl.h"
#endif //TINYSTL_HASH_H
