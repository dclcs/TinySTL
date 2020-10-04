//
// Created by dcl_1 on 2020/9/17.
//

#ifndef TINYSTL_DEQUE_H
#define TINYSTL_DEQUE_H
#include "../allocator/alloc.h"
#include "../iterator/iterator.h"

namespace TinySTL{

    /**
     * n != 0 return n;
     * n == 0 : 使用默认值
     *  sz < 512 : return 512 / sz
     *  sz >= 512 : retun 1
     * @param n
     * @param sz
     * @return
     */
    inline size_t __deque_buf_size(size_t n, size_t sz){
        return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
    }

    /*deque iteartor*/
    template<class T , class Ref, class Ptr, size_t BufSiz>
    struct __deque_iterator{
        typedef __deque_iterator<T, T&, T*, BufSiz>     iterator;
        typedef __deque_iterator<T, const T&, const T*, BufSiz>     const_iterator;
        static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T));}

        typedef random_access_iterator_tag  iterator_category;
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T** map_pointer;

        typedef __deque_iterator self;

        T *cur;
        T *first;
        T *last;
        map_pointer node;
        __deque_iterator(T *_x, map_pointer _y): cur(_x), first(*_y), last(*_y + buffer_size()), node(_y){}
        __deque_iterator():cur(0), first(0), last(0), node(0) {}
        __deque_iterator(const iterator& _x) : cur(_x.cur), first(_x.first), last(_x.last), node(_x.node) {}

        void set_node(map_pointer new_node){
            node = new_node;
            first = *new_node;
            last = first + difference_type(buffer_size());
        }

        reference operator*() const {return *cur;}
        pointer operator->() const {return &(operator*());}

        difference_type  operator- (const self& x) const {
            return difference_type(buffer_size()) * (node - x.node - 1) +
                    (cur - first) + (x.last - x.cur);
        }

        self& operator++() {//前置式
            ++ cur;
            if(cur == last){
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        self operator++(int){//后置式
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self& operator--(){
            if(cur == first){
                set_node(node - 1);
                cur = last;
            }
            --cur;
            return *this;
        }

        self operator--(int){
            self tmp = *this;
            --*this;
            return tmp;
        }

        self& operator+=(difference_type n){
            difference_type offset = n + (cur - first);
            if(offset >= 0 && offset < difference_type(buffer_size()))
                cur += n;
            else{
                difference_type node_offset =
                        offset > 0 ? offset / difference_type (buffer_size())
                                    : -difference_type ((-offset - 1) / buffer_size()) - 1;
                set_node(node + node_offset);
                cur = first + (offset - node_offset * difference_type(buffer_size()));
            }
            return *this;
        }


        self operator+(difference_type n) const {
            self tmp = *this;
            return tmp += n;
        }

        self& operator-=(difference_type n) {return *this += -n;}
        self operator-(difference_type n) const {
            self tmp = *this;
            return tmp -= n;
        }

        reference operator[](difference_type n) const { return *(*this + n);}

        bool operator ==(const self& x) const {return cur == x.cur;}
        bool operator != (const self& x) const {return !(*this == x );}
        bool operator < (const self& x) const {
            return (node == x.node) ? (cur < x.cur) : (node < x.node);
        }

    };

    template<class T, class alloc=MyAlloc, size_t BufSiz = 0>
    class deque{
    public:
        typedef     T               value_type;
        typedef     T&              reference;
        typedef     value_type *    pointer;
        typedef     size_t          size_type;
        typedef     ptrdiff_t       difference_type;

        typedef __deque_iterator<T, T*, T&, BufSiz> iterator;

    protected:
        typedef simple_alloc<value_type, MyAlloc> data_allocator;
        typedef simple_alloc<pointer, MyAlloc> map_allocator;
        typedef     pointer*    map_pointer;

    protected:
        iterator    start;
        iterator    finish;
        map_pointer     map;
        size_type       map_size;


    public:
        // 构造函数
        deque(): start() , finish() , map_size(0){}

        deque(int n, const value_type& value):start(), finish(), map(0), map_size(0){
            fill_initialize(n, value);
        }


//        size_t buffer_size(){return __deque_buf_size(BufSiz, sizeof(T));}
        void fill_initialize(size_type n, value_type value);
        void create_map_and_nodes(size_type n);
        size_t initial_map_size() { return 8;};

        iterator begin() {return start;}
        iterator end() { return finish; }
        reference operator[] (size_type n){
            return start[difference_type(n)];
        }
        reference front() {return *start;}
        reference back() {
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }
        size_type size() const {return finish - start;;}
        size_type max_size() const {return size_type(-1);}
        bool empty() const {return finish == start;}

        pointer allocate_node() {return data_allocator ::allocate(iterator::buffer_size());}

    };
}

#include "deque_impl.h"
#endif //TINYSTL_DEQUE_H
