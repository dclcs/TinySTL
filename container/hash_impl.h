//
// Created by dcl on 2020/10/6.
//

#ifndef TINYSTL_HASH_IMPL_H
#define TINYSTL_HASH_IMPL_H
#include "hash.h"
namespace TinySTL{
    template <class V, class K, class HF, class ExK, class EqK, class A>
    __hashtable_iterator<V, K, HF, ExK, EqK, A>&
    __hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++() {
        const node* old = cur;
        cur = cur->next;
        if(!cur){
            //find the next bucket
            size_type bucket = ht->bkt_num(old->val);
            while(!cur && ++bucket < ht->buckets.size()){
                cur = ht->buckets[bucket];
            }
        }

        return *this;
    }

    template <class V, class K, class HF, class ExK, class EqK, class A>
    inline __hashtable_iterator<V, K, HF, ExK, EqK, A>
    __hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++(int) {
        iterator tmp = *this;
        ++*this;
        return tmp;
    }


    template <class V, class K, class HF, class ExK, class EqK, class A>
    void hashtable<V, K, HF, ExK, EqK, A>::resize(size_type num_elements_hint) {
        const size_type old_n = buckets.size();
        if(num_elements_hint > old_n){
            const size_type  n = next_size(num_elements_hint);
            if(n > old_n){
                vector<node*, A> tmp(n, (node*)0);
                for(size_type bucket = 0; bucket < old_n ; bucket ++){
                    node* first = buckets[bucket];
                    while (first){
                        size_type new_bucket = bkt_num(first->val, n);
                        buckets[bucket] = first->next;
                        first->next = tmp[new_bucket];
                        tmp[new_bucket] = first;
                        first = buckets[bucket];
                    }
                }
                buckets.swap(tmp);
            }
        }
    }
}//end namespace



#endif //TINYSTL_HASH_IMPL_H
