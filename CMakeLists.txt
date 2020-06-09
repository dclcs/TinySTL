cmake_minimum_required(VERSION 3.5)
project(TinySTL)

set(CMAKE_CXX_STANDARD 11)

add_executable(TinySTL main.cpp container/vector.h container/vector.impl.h allocator/alloc.h allocator/alloc.impl.h)