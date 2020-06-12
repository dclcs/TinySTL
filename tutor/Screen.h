//
// Created by dcl_1 on 2020-6-11.
//

#ifndef TINYSTL_SCREEN_H
#define TINYSTL_SCREEN_H
#include <cstddef>
#include <iostream>
using namespace std;

class Screen {
public:
    Screen(int x): i(x){}
    int get(){return i;}

    void *operator new(std::size_t);
    void operator delete(void*, size_t);

private:
    Screen* next;
    static Screen* freeStore;
    static const int screenChunk;
private:
    int i;
};


#endif //TINYSTL_SCREEN_H
