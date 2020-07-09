//
// Created by dcl_1 on 2020-7-9.
//

#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H
namespace TinySTL{
    template<class T1, class T2>
    inline void construct(T1* p, const T2& value){
        new (p) T1 (value);
    }


    //destory
    template <class T>
    inline void destory(T* pointer){
        pointer->~T();
    }
    template <class ForwardIter>
    inline void __destory_aux(ForwardIter first, ForwardIter last){
        for(; first < last; first ++){
            destory(&*first);
        }
    }
    template <class ForwardIteror/*, class T*/>
    inline void __destory(ForwardIteror first, ForwardIteror last/*, T* */){
        __destory_aux(first, last);
    }
    template <class ForwardIterator>
    inline void
    destory(ForwardIterator first, ForwardIterator last){
        __destory(first, last);
    }

}


#endif //TINYSTL_CONSTRUCT_H
