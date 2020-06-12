//
// Created by dcl_1 on 2020-6-11.
//

#include "Screen.h"
Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void* Screen::operator new(std::size_t size) {
    Screen *p;
    if(!freeStore){
        //linked list 是空的，所以申请一大块内存
        std::size_t chunk = screenChunk * size; // 24 * 16
        freeStore = p =
                reinterpret_cast<Screen*>(new char[chunk]);
        for(; p!=&freeStore[screenChunk-1]; ++p)
            p->next = p + 1;
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;

}

void Screen::operator delete(void * p, size_t) {
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}