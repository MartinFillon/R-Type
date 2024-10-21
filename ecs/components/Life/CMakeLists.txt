cmake_minimum_required(VERSION 3.27)

add_library(life SHARED src/lib.cpp)
target_include_directories(life PRIVATE ../../include)
target_include_directories(life PRIVATE ../../../protocol/include)
