//
// Created by dcl_1 on 2020-6-9.
//

#ifndef TINYSTL_ALLOC_H
#define TINYSTL_ALLOC_H
namespace TinySTL{
    /**
     * 第二级分配器
     */
    #include <cstdlib>
    template<class T, class alloc>
    class simple_alloc{
        //allocator访问接口
    public:
        static  T *allocate(size_t n){
            return 0 == n ? 0 : (T*) alloc::allocate(n * sizeof(T));
        }
        static void deallocate(T* p, size_t n){
            if(0 != n) alloc::deallocate(p, n*sizeof(T));
        }
    };



     const size_t __ALIGN = 8;
     const size_t __MAX_BYTES = 128;
     const size_t __NFREELISTS = __MAX_BYTES / __ALIGN; // 16

     class MyAlloc{
     private:
         static size_t ROUND_UP(size_t bytes){

             return ( ((bytes) + __ALIGN - 1 ) & ~(__ALIGN - 1) );
         }

     private:
         union obj{
             union obj* free_list_link;
         };
     private:
         static obj* free_list[__NFREELISTS];
         static size_t FREELIST_INDEX(size_t bytes){
             /**
              * If we want 17 bytes:
              *     we can get (17 + 8 - 1) / 8 - 1 = 2
              */
             return (((bytes) + __ALIGN - 1 ) / __ALIGN - 1);
         }

         //Returns an object of size n , and optionally adds to size n free list
         static void* refill(size_t n);
         //TODO: Add refill

         static char* chunk_alloc(size_t size, int &nobjs);

         static char* start_free;
         static char* end_free;
         static size_t heap_size;

     public:
         static void *allocate(size_t n);
         static void deallocate(void *p, size_t n);

     };
}
#include "alloc.impl.h"
#endif //TINYSTL_ALLOC_H
