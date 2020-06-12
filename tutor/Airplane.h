//
// Created by dcl_1 on 2020-6-11.
//

#ifndef TINYSTL_AIRPLANE_H
#define TINYSTL_AIRPLANE_H
#include <cstddef>


class Airplane {
private:
    struct AirplaneRep{
        unsigned long miles;
        char type;
    };
private:
    union {
        AirplaneRep rep;
        Airplane* next;
    };

public:
    static void* operator new(size_t size);
    static void operator delete(void* deadObject, size_t size);

private:
    static const int BLOCK_SIZE;
    static Airplane* headOfFreeList;
};


#endif //TINYSTL_AIRPLANE_H
