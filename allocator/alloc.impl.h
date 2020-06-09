//
// Created by dcl_1 on 2020-6-9.
//

#ifndef TINYSTL_ALLOC_IMPL_H
#define TINYSTL_ALLOC_IMPL_H
#include "alloc.h"

namespace TinySTL{
    char *Alloc::start_free = 0;
    char *Alloc::end_free = 0;
    size_t Alloc::heap_size = 0;

    Alloc::obj *Alloc::free_list[Alloc::ENFreeLists::NFREELISTS] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    void *Alloc::allocate(size_t bytes) {
        if( bytes > EMaxBytes::MAXBYTES ){
            return malloc(bytes);
        }
        size_t index = FREELIST_INDEX(bytes);
        obj *list = free_list[index];
        if(list){
            free_list[index] = list->next;
            return list;
        } else{
            return refill(ROUND_UP(bytes));
        }
    }

}
#endif //TINYSTL_ALLOC_IMPL_H
