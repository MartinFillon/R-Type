cmake_minimum_required(VERSION 3.27)

add_library(OutlinedColor SHARED src/lib.cpp)
target_include_directories(OutlinedColor PRIVATE ../../include)
target_include_directories(OutlinedColor PRIVATE ../../../protocol/include)
