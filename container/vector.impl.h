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
            copy_backward(position, finish - 2, finish - 1);
            *position = copy;
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


    template<class T, class alloc>
    void vector<T, alloc>::insert(vector::iterator position, vector::size_type n, const T &x) {
        if(n != 0){
            if(size_type(end_of_storge - finish) >= n){
                //备用空间大于等于新增元素
                T x_copy = x;
                // 以下计算插入点之后的现有元素个数
                const size_type elem_after = finish - position;
                iterator old_finish = finish;
                if(elem_after > n){
                    //插入到之后的现有元素 大于 新增元素
                    uninitialized_copy(finish - n, finish, finish);
                    finish += n;
                    copy_backward(position, old_finish - n, old_finish);
                    fill(position, position + n, x_copy);
                }else{
                    //插入到之后的现有元素 小于等于 新增元素
                    uninitialized_fill_n(finish, n - elem_after, x_copy);
                    finish += n - elem_after;
                    uninitialized_copy(position, old_finish, finish);
                    finish += elem_after;
                    fill(position, old_finish, x_copy);
                }
            }else{
                //备用空间小于 “新增元素”个数
                //首先决定长度，旧长度的两倍
                const size_type old_size = size();
                const size_type len = old_size + max(old_size, n);
                //以下配置新的vector空间
                iterator new_start = data_allocator::allocate(len);
                iterator new_finish = new_start;
                try {
                    new_finish = uninitialized_copy(start, position, new_start);
                    new_finish = uninitialized_fill_n(new_finish, n, x);
                    new_finish = uninitialized_copy(position, finish, new_finish);
                } catch (...) {
                    destory(new_start, new_finish);
                    data_allocator::deallocate(new_start, len);
                    throw ;
                }

                destory(start, finish);
                deallocate();
                start = new_start;
                finish = new_finish;
                end_of_storge = new_start + len;

            }
        }
    }




}

#endif //TINYSTL_VECTOR_IMPL_H
