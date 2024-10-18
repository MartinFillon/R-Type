cmake_minimum_required(VERSION 3.27)

add_library(controllable SHARED src/lib.cpp)
target_include_directories(controllable PRIVATE ../../include)
target_include_directories(controllable PRIVATE ../../../protocol/include)
