cmake_minimum_required(VERSION 3.5)
project(TinySTL)

set(CMAKE_CXX_STANDARD 11)

add_executable(TinySTL main.cpp container/vector.h container/vector.impl.h allocator/alloc.h allocator/alloc.impl.h tutor/Screen.cpp tutor/Screen.h tutor/Airplane.cpp tutor/Airplane.h tutor/allocator.cpp tutor/allocator.h)