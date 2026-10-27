cmake_minimum_required(VERSION 4.1)
project(oop_26Kpi)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(/utf-8)

add_executable(lab1 WIN32 lab1/MyProg.cpp
        lab1/module1.h
        lab1/module2.h
        lab1/utils.h
)

add_executable(lab2 WIN32
)