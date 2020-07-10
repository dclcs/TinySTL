//
// Created by dcl_1 on 2020-6-9.
//
#ifndef TINYSTL_VECTOR_IMPL_H
#define TINYSTL_VECTOR_IMPL_H
#include "vector.h"

namespace TinySTL{

    template<class T, class alloc>
    void vector<T, alloc>::insert_aux(vector::iterator position, const T &x) {
        if(finish != end_of_storge){
            construct(finish, *(finish - 1));
            ++finish;
            //copy_backward();
        }else{
            const size_type old_size = size();
            const size_type len = old_size != 0 ? 2 * old_size : 1;
            //如果大小为0， 则配置1；如果原大小不为0 则为原来的两倍
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;

            try {

                new_finish = uninitialized_copy(start, position, new_start);
                construct(new_finish, x);
                ++new_finish;
                new_finish = uninitialized_copy(position, finish, new_finish);
            }
            catch (...) {
                destory(new_start, new_finish);
                data_allocator::deallocate(new_start, len);
                throw ;
            }

            destory(begin(), end());
            deallocate();

            start = new_start;
            finish = new_finish;
            end_of_storge = new_start + len;
        }
    }




}

#endif //TINYSTL_VECTOR_IMPL_H
