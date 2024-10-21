cmake_minimum_required(VERSION 3.27)

add_library(size SHARED src/lib.cpp)
target_include_directories(size PRIVATE ../../include)
target_include_directories(size PRIVATE ../../../protocol/include)
