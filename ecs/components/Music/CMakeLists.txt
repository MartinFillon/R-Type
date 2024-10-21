cmake_minimum_required(VERSION 3.27)

add_library(music SHARED src/lib.cpp)
target_include_directories(music PRIVATE ../../include)
target_include_directories(music PRIVATE ../../../protocol/include)
