//
// Created by dcl_1 on 2020-7-13.
//

#ifndef TINYSTL_LIST_IMPL_H
#define TINYSTL_LIST_IMPL_H
#include "list.h"

namespace TinySTL{
    template<class T, class alloc>
    void list<T, alloc>::clear() {
        link_type cur = (link_type) node->next;
        while(cur != node){
            link_type tmp = cur;
            cur = (link_type) cur->next;
            destory_node(tmp);
        }
        node->next = node;
        node->prev = node;
    }

    template<class T, class alloc>
    void list<T, alloc>::remove(const T &value) {
        list_iterator first = begin();
        list_iterator last = end();
        while(first != last){
            list_iterator  next = first;
            ++next;
            if(*first == value) erase(first);
            first = next;
        }
    }

    template<class T, class alloc>
    void list<T, alloc>::transfer(list::list_iterator position, list::list_iterator first, list::list_iterator last) {
        if(position != last){
            (*(link_type((*last.node).prev))).next = position.node;
            (*(link_type((*first.node).prev))).next = last.node;
            (*(link_type((*position.node).prev))).next = first.node;
            link_type  tmp = link_type ((*position.node).prev);
            (*position.node).prev = (*last.node).prev;
            (*last.node).prev = (*first.node).prev;
            (*first.node).prev = tmp;
        }
    }

    template<class T, class alloc>
    void list<T, alloc>::merge(list <T, alloc> &x) {
        list_iterator first1 = begin();
        list_iterator last1 = end();
        list_iterator first2 = x.begin();
        list_iterator last2 = x.end();

        while(first1 != last1 && first2 != last2){
            if(*first1 < *first2){
                list_iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            }else
                ++first1;
        }
        if(first2 != last2) transfer(last1, first2, last2);
    }

    template<class T, class alloc>
    void list<T, alloc>::reverse() {
        if(node->next == node || link_type(node->next)->next == node) return;

        list_iterator first = begin();
        ++first;
        while(first != end()){
            list_iterator old = first;
            ++first;
            transfer(begin(), old, first);
        }
    }

    template<class T, class alloc>
    void list<T, alloc>::sort() {
        if(node->next == node || link_type(node->next)->next == node) return;

        list<T, alloc> carry;
        list<T, alloc> counter[64];
        int fill = 0;
        while(!empty()){
            carry.splice(carry.begin(), *this, begin());
            int i = 0 ;
            while (i < fill && !counter[i].empty()){
                counter[i].merge(carry);
                carry.swap(counter[i++]);
            }
            carry.swap(counter[i]);
            if(i == fill) ++fill;
        }

        for(int i = 1; i < fill ; i ++){
            counter[i].merge(counter[i - 1]);
        }
        swap(counter[fill - 1]);
    }

    template<class T, class alloc>
    void list<T, alloc>::swap(list & x) {
        std::swap(node, x.node);
    }


}//end TinySTL
#endif //TINYSTL_LIST_IMPL_H
