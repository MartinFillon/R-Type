cmake_minimum_required(VERSION 3.27)

add_library(text SHARED src/lib.cpp)
target_include_directories(text PRIVATE ../../include)
target_include_directories(text PRIVATE ../../../protocol/include)
