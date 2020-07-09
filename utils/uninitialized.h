//
// Created by dcl_1 on 2020-7-9.
//

#ifndef TINYSTL_UNINITIALIZED_H
#define TINYSTL_UNINITIALIZED_H
namespace TinySTL{
    #include "../utils/construct.h"

    template<class ForwardIterator , class Size, class T>
    inline ForwardIterator
    __uninitialized_fill_n_aux(ForwardIterator first, Size n,
                               const T&x /*, __false_type*/){
        ForwardIterator cur = first;
        for(; n > 0; --n, ++ cur){
//            new ((T*)cur + n) T (x);
            TinySTL::construct((T*)cur, x);
        }
        return cur;
    }

    template<class ForwardIterator , class Size, class T /*, class T1*/>
    inline ForwardIterator
    __uninitialized_fill_n(ForwardIterator first,
                                                  Size n, const T& x/*,T1 * */){
        //typedef typename __type_traits<T1>::is_POD_type is_POD;
        return __uninitialized_fill_n_aux(first, n, x /*, is_POD()*/);
    }
    template<class ForwardIterator , class Size, class T>
    inline ForwardIterator
    uninitialized_fill_n(ForwardIterator first,
                                                Size n, const T& x){
        return __uninitialized_fill_n(first, n, x);
    }





    template<class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last,
                            const T& x){
        //uninitialized_fill()会在[first, last)为内的每个迭代器，调用construct(&*i, x)

        __uninitialized_fill(first, last, x);
    }


    template<class ForwardIterator, class T, class T1>
    void __uninitialized_fill(ForwardIterator first, ForwardIterator last,
                              const T& x/*, T1 * */){
        //typedef typename __type_traits<T1>::is_POD_type is_POD;
        __uninitalized_fill_aux(first, last, x /*, is_POD*/);
    }


    template<class ForwardIterator, class T>
    inline void __uninitalized_fill_aux(ForwardIterator first, ForwardIterator last,
                                        const T& x /*,__false_type*/){
        ForwardIterator cur = first;
        for(; cur != last; cur ++){
//            new ((T*)cur + i) T (0);
        }
    }
}

#endif //TINYSTL_UNINITIALIZED_H
