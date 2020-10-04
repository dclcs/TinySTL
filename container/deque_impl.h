//
// Created by dcl_1 on 2020/9/24.
//

#ifndef TINYSTL_DEQUE_IMPL_H
#define TINYSTL_DEQUE_IMPL_H
#include "deque.h"
namespace TinySTL{
    template<typename T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::fill_initialize(size_type n, value_type value) {
        create_map_and_nodes(n);
    }


    template<class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::create_map_and_nodes(size_type num_elements) {
        size_type num_nodes = num_elements / iterator::buffer_size() + 1;


        // 一个map 要管理几个节点，最少8个， 最多是"所需节点+2"
        map_size = max(initial_map_size() , num_nodes + 2);
        map = map_allocator::allocate(map_size);

        //配置一个具有map_size个的节点
        map_pointer nstart = map + (map_size - num_nodes) / 2;
        map_pointer nfinish = nstart + num_nodes - 1;

        map_pointer cur;

        for(cur = nstart ; cur <= nfinish ; ++cur){
            *cur = allocate_node();
        }

        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur = start.first;
        finish.cur = finish.first + num_elements % iterator::buffer_size();
    }
}
#endif //TINYSTL_DEQUE_IMPL_H
