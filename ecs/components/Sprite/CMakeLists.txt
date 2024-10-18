cmake_minimum_required(VERSION 3.27)

add_library(sprite SHARED src/lib.cpp)
target_include_directories(sprite PRIVATE ../../include)
target_include_directories(sprite PRIVATE ../../../protocol/include)
