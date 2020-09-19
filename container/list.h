//
// Created by dcl_1 on 2020-7-12.
//

#ifndef TINYSTL_LIST_H
#define TINYSTL_LIST_H
#include "../iterator/iterator.h"
#include "../allocator/alloc.h"
namespace TinySTL{
    template <class T>
    struct __list_node{
        typedef void* void_pointer;
        void_pointer prev;
        void_pointer next;
        T data;
    };
//双向链表

    template <class T, class Ref, class Ptr>
    struct __list_iterator{
        typedef     __list_iterator<T, T&, T*>      iterator;
        typedef     __list_iterator<T, Ref, Ptr>    self;

        typedef     bidirectional_iterator_tag      iterator_category;
        typedef     T                               value_type;
        typedef     Ptr                             pointer;
        typedef     Ref                             reference;
        typedef     __list_node<T>*                 link_type;
        typedef     size_t                          size_type;
        typedef     ptrdiff_t                       difference_type;

        link_type   node;

        //constructor
        __list_iterator(){}
        __list_iterator(link_type x): node(x) {}
        __list_iterator(const iterator& x): node(x.node) {}

        bool operator==(const self& x) const {return node == x.node;}
        bool operator!=(const self& x) const {return node != x.node;}
        //以下对迭代器取值(dereference)，取得是结点得数据值
        reference operator*() const {return (*node).data;}

        //以下对迭代器得成员(member access)运算子得标准做法
        pointer operator->() const {return &(operator*());}
        //迭代器+1
        self& operator++(){
            node = (link_type)((*node).next);
            return *this;
        }
        self operator++(int){
            self tmp = *this;
            ++*this;
            return tmp;
        }

        //迭代器-1
        self& operator--(){
            node = (link_type)((*node).prev);
            return *this;
        }
        self operator--(int){
            self tmp = *this;
            --*this;
            return tmp;
        }

    };

    template<class T, class alloc = MyAlloc>
    class list{
    public:
        typedef     T       value_type;
        typedef     size_t  size_type;
        typedef     T&      reference;
        typedef     __list_iterator<value_type, reference, value_type*> list_iterator;
        typedef     __list_iterator<value_type, const reference, const value_type*> const_list_iterator;

    protected:

        typedef __list_node<T> list_node;
        typedef simple_alloc<list_node, alloc> list_node_allocator;


    public:
        typedef list_node * link_type;
        //construct
        list() {empty_initialize();} //创建一个空的list
        list_iterator begin() { return (link_type)((*node).next);}
        const_list_iterator begin() const {return (link_type)((*node).next);}
        list_iterator end() {return node;}
        const_list_iterator end() const {return node;}
        bool empty() const {return node->next == node; }
        size_type size() const {
            size_type result = 0;
            distance(begin(), end(), result);
            return result;
        }
        reference front() {return *begin();}
        reference back() {return *(--end());}
        list_iterator insert(list_iterator position, const T& x){
            link_type tmp = create_node(x);
            tmp->next = position.node;
            tmp->prev = position.node->prev;
            (link_type(position.node->prev))->next = tmp;
            position.node->prev = tmp;
            return tmp;
        }



        void push_back(const T& x){
            insert(end(), x);
        }
        void push_front(const T& x){
            insert(begin(), x);
        }

        list_iterator erase(list_iterator position){
            link_type next_node = link_type(position.node->next);
            link_type prev_node = link_type(position.node->prev);
            prev_node->next = next_node;
            next_node->prev = prev_node;
            destory_node(position.node);
            return list_iterator (next_node);
        }

        void pop_front(){erase(begin());}
        void pop_back(){
            list_iterator tmp = end();
            erase(--tmp);
        }

        void splice(list_iterator position, list& x){
            if(!x.empty()){
                transfer(position, x.begin(), x.end());
            }
        }

        void splice(list_iterator position, list&, list_iterator i){
            list_iterator  j = i;
            ++j;
            if(position == i || position == j) return;
            transfer(position, i, j);
        }

        void splice(list_iterator position, list_iterator first, list_iterator last){
            if(first != last) transfer(position, first, last);
        }
        void clear();
        void remove(const T& value);
        //将[first, last)内容移动到position之前
        void transfer(list_iterator position, list_iterator first, list_iterator last);
        //将x合并到*this上,前提：两个链表已经排序
        void merge(list<T, alloc>& x);

        void reverse();

        void sort();

        void swap(list&);
    protected:
        link_type node;
        // 配置一个节点并返回
        link_type get_node() {return list_node_allocator::allocate(); }
        //释放一个节点
        void put_node(link_type p) {list_node_allocator ::deallocate(p);}
        link_type create_node(const T& x){
            link_type p = get_node();
            construct(&p->data, x);
            return p;
        }

        void destory_node(link_type p){
            destory(&p->data);
            put_node(p);
        }
        void empty_initialize(){
            node = get_node();
            node->next = node;
            node->prev = node;
        }
    };




}

#include "list_impl.h"

#endif //TINYSTL_LIST_H
