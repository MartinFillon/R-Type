cmake_minimum_required(VERSION 3.27)

add_library(animation SHARED src/lib.cpp)
target_include_directories(animation PRIVATE ../../include)
target_include_directories(animation PRIVATE ../../../protocol/include)
