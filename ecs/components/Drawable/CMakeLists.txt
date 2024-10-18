cmake_minimum_required(VERSION 3.27)

add_library(drawable SHARED src/lib.cpp)
target_include_directories(drawable PRIVATE ../../include)
target_include_directories(drawable PRIVATE ../../../protocol/include)
