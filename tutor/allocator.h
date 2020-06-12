//
// Created by dcl_1 on 2020-6-11.
//

#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H

#include <cstddef>
class allocator {
private:
    struct obj{
        struct obj* next;
    };
public:
    void *allocate(size_t);
    void deallocate(void*, size_t);

private:
    obj* freeStore = nullptr;
    const int CHUNK = 5;

};


#endif //TINYSTL_ALLOCATOR_H
