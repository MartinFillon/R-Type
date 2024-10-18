cmake_minimum_required(VERSION 3.27)

add_library(destroyable SHARED src/lib.cpp)
target_include_directories(destroyable PRIVATE ../../include)
target_include_directories(destroyable PRIVATE ../../../protocol/include)
