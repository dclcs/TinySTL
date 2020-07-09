//
// Created by dcl_1 on 2020-6-9.
//
#ifndef TINYSTL_VECTOR_IMPL_H
#define TINYSTL_VECTOR_IMPL_H
#include "vector.h"

namespace TinySTL{

//    template <class T, class alloc>
//    vector<T,alloc>::vector(const size_type n){
//        //应该要有一个allocator 由allocator来分配
//        start = (iterator)alloc::allocate(n);
//        int i  = 0;
//        for( ; i != n ; i ++){
//            new ((T*)start + i) T (0);
//        }
//        finish = end_of_storge = start + n;
//    }
//
//    template<class T, class alloc>
//    vector<T, alloc>::vector(const vector::size_type n, const value_type &value) {
//        start = (iterator)alloc::allocate(n);
//        int i  = 0;
//        for( ; i != n ; i ++){
//            new ((T*)start + i) T (value);
//        }
//        finish = end_of_storge = start + n;
//    }




}

#endif //TINYSTL_VECTOR_IMPL_H
