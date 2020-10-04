//
// Created by dcl_1 on 2020/9/24.
//

#ifndef TINYSTL_DEQUE_IMPL_H
#define TINYSTL_DEQUE_IMPL_H
#include "deque.h"
namespace TinySTL{
    template<typename T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::fill_initialize(size_type n, value_type value) {
        create_map_and_nodes();
    }


    template<class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::create_map_and_nodes(size_type num_elements) {
        size_type num_nodes = num_elements / iterator::buffer_size() + 1;
    }
}
#endif //TINYSTL_DEQUE_IMPL_H
