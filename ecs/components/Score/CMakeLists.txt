cmake_minimum_required(VERSION 3.27)

add_library(score SHARED src/lib.cpp)
target_include_directories(score PRIVATE ../../include)
target_include_directories(score PRIVATE ../../../protocol/include)
