//
// Created by dcl_1 on 2020-7-10.
//

#ifndef TINYSTL_ALGOBASE_H
#define TINYSTL_ALGOBASE_H
namespace TinySTL{
#include <iostream>
    ///////////////////////////////////////////////////////////////////////////
    //                          copy
    ///////////////////////////////////////////////////////////////////////////

    template<class RandomAccessIterator, class OutputIterator, class Distance>
    inline OutputIterator
    __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*){
        for(Distance n = last - first; n > 0; --n, ++result, ++first){
            *result = *first;
        }
        return result;
    }

    template<class T>
    inline T* __copy_t(const T * first, const T * last, T * result){
        return __copy_d(first, last, result,(T*) 0);
    }

    template<class InputIterator, class OutputIterator>
    struct __copy_dispatch{
        OutputIterator operator()(InputIterator first, InputIterator last,
                OutputIterator result){
            return result;
        }
    };

    template<class T>
    struct __copy_dispatch<T*, T*>{
        T* operator()(T* first, T* last, T* result){
            std::cout << "speci" << std::endl;
            return __copy_t(first, last, result);
        }
    };


    template<class InputIterator, class OutputIterator>
    inline OutputIterator copy(InputIterator first, InputIterator last,
            OutputIterator result){
        return __copy_dispatch<InputIterator, OutputIterator>()
                (first, last, result);
    }
}
#endif //TINYSTL_ALGOBASE_H
