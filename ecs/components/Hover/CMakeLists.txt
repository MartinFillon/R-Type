cmake_minimum_required(VERSION 3.27)

add_library(hover SHARED src/lib.cpp)
target_include_directories(hover PRIVATE ../../include)
target_include_directories(hover PRIVATE ../../../protocol/include)
