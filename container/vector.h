//
// Created by dcl_1 on 2020-6-9.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H
#include "../allocator/alloc.h"
#include "../utils/construct.h"
#include "../utils/uninitialized.h"
#include "../algorithms/algobase.h"
#include <iostream>

namespace TinySTL{

    template <class T, class alloc = MyAlloc>
    class vector{

    public://typedef
        typedef     T               value_type;
        typedef     value_type *    iterator;
        typedef     const T*        const_iterator;
        typedef     value_type &    reference;
        typedef     size_t          size_type;
//        typedef     ptrdiff_t       difference_type;
    protected:
        typedef     simple_alloc<value_type, alloc> data_allocator;
        iterator    start;          //目前使用空间的头
        iterator    finish;         //目前使用空间的尾
        iterator    end_of_storge;  //可以使用空间的尾
        void insert_aux(iterator position, const T& x);
        void deallocate(){
            if(start){
                data_allocator::deallocate(start, end_of_storge - start);
            }
        }
        void fill_initialize(size_type n, const T& value){
            start = allocate_and_fill(n, value);
            finish = start +n;
            end_of_storge = finish;
        }
    public:
        //构造函数
        vector(): start(0), finish(0) ,end_of_storge(0){ }
        explicit vector(size_type n ){ fill_initialize(n, T());}
        vector( size_type n , const T& value ) { fill_initialize(n, value);}
        //析构函数
        ~vector(){
            destory(start, finish);
            deallocate();
        }
        //接口
        iterator begin() { return start;}
        const_iterator begin() const { return start; }
        iterator end(){ return finish;}
        const_iterator end() const {return finish;}

        size_type size() const
        { return size_type( ( end() - begin() ) );}

        size_type  capacity() const
        { return size_type( end_of_storge - begin() );}

        bool empty() const { return end() == begin(); }

        reference operator[] (size_type n) {return *(begin() + n);}

        reference front() { return *begin();}
        reference back() {return *(end() - 1);}

        //TODO:Finish push_back and pop
        void push_back( const T& x){
            if(finish != end_of_storge){//还有备用空间

                construct(finish, x);
                ++finish;
            }else{//无备用空间
                //TODO::Implement the insert_aux
                insert_aux(end(), x);
            }
        }

        void pop_back(){
            --finish;
            destory(finish);
        }

        iterator erase(iterator position){
            if(position + 1 != end()){
                copy(position + 1, finish, position);
            }
            --finish;
            destory(finish);
            return position;
        }
        //[first, last)
        iterator erase(iterator first, iterator last){
            iterator i = copy(last, finish, first);
            destory(i, finish);
            finish = finish - (last - first);
            return first;
        }

        iterator clear(){erase(begin(), end());}
        //从position开始，插入n个元素，元素初值为x
        void insert(iterator position, size_type n, const T& x);

    protected:
        iterator allocate_and_fill(size_type n, const T& x){
            iterator result = data_allocator::allocate(n);
            uninitialized_fill_n(result, n, x);
            return result;
        }
    };


}

#include "vector.impl.h"
#endif //TINYSTL_VECTOR_H
