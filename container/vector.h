//
// Created by dcl_1 on 2020-6-9.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H
namespace TinySTL{
    template <class T>
    class vector{
    private:
        T* _start;
        T* _end;
    public://typedef
        typedef int size_type;
    public:
        vector(): _start(0), _end(0) { }
        explicit vector(const size_type n );
    };
}

#include "vector.impl.h"
#endif //TINYSTL_VECTOR_H
