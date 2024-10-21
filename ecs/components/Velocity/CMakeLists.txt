cmake_minimum_required(VERSION 3.27)

add_library(velocity SHARED src/lib.cpp)
target_include_directories(velocity PRIVATE ../../include)
target_include_directories(velocity PRIVATE ../../../protocol/include)
