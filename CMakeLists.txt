cmake_minimum_required(VERSION 3.14)
project(Assignment4)

set(CMAKE_CXX_STANDARD 14)

add_executable(mergesort
        src/main.cpp src/MergeSort.cpp src/MergeSort.h)

set(CMAKE_CXX_FLAGS "-static")
