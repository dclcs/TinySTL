//
// Created by dcl_1 on 2020-6-9.
//
#ifndef TINYSTL_VECTOR_IMPL_H
#define TINYSTL_VECTOR_IMPL_H
#include "vector.h"

namespace TinySTL{

    template <class T>
    vector<T>::vector(const size_type n){
        //应该要有一个allocator 由allocator来分配
        std::cout << "TinySTL vector allocator" << std::endl;
        void* i = allco.allocate(n);

    }
}

#endif //TINYSTL_VECTOR_IMPL_H
