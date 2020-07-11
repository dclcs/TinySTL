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
            return __copy_t(first, last, result);
        }
    };

    //将[first, last) 复制到[result, result + last -first)
    template<class InputIterator, class OutputIterator>
    inline OutputIterator copy(InputIterator first, InputIterator last,
            OutputIterator result){
        return __copy_dispatch<InputIterator, OutputIterator>()
                (first, last, result);
    }


    ///////////////////////////////////////////////////////////////////////////
    //                          copy_backwawrd
    // description:
    //              将[first, last)区间的每一个元素，以逆序的方式复制到以
    //              result + 1 为起点，方向亦为逆序的区间上。
    ///////////////////////////////////////////////////////////////////////////

    template<class BidirectionalIterator1, class BidirectionalIterator2, class Distance>
    inline BidirectionalIterator2
    __copy_backward_d(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result, Distance*){
        for(Distance n = last - first; n > 0; --n, ++result, --last){
            *result = *last;
        }
        return result;
    }

    template<class T>
    inline T* __copy_backward_t(const T * first, const T * last, T * result){
        return __copy_backward_d(first, last, result,(T*) 0);
    }

    template<class BidirectionalIterator1, class BidirectionalIterator2>
    struct __copy_backward_dispatch{
            BidirectionalIterator2 operator() (BidirectionalIterator1 first, BidirectionalIterator1 last,
                                               BidirectionalIterator2 result){
                return result;
            }
        };

    template<class T>
    struct __copy_backward_dispatch<T*, T*>{
        T* operator()(T* first, T* last, T*result){
            return __copy_backward_t(first, last, result);
        }
    };

    template<class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
                                                BidirectionalIterator1 last,
                                                BidirectionalIterator2 result){
        return __copy_backward_dispatch<BidirectionalIterator1, BidirectionalIterator2>()
                (first, last, result);
    }
    ///////////////////////////////////////////////////////////////////////////
    //                          fill
    // description:
    //              将[first, last)内将所有的元素该填新值
    ///////////////////////////////////////////////////////////////////////////
    template <class ForwardIterator , class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value){
        for(; first != last; ++first){
            *first = value;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //                          max
    // description:
    //              两个对象比较大小
    ///////////////////////////////////////////////////////////////////////////
    template <class T>
    inline const T& max(const T& a, const T& b){
        return a < b ? b : a;
    }

}
#endif //TINYSTL_ALGOBASE_H
