cmake_minimum_required(VERSION 3.27)

add_library(FilledColor SHARED src/lib.cpp)
target_include_directories(FilledColor PRIVATE ../../include)
target_include_directories(FilledColor PRIVATE ../../../protocol/include)
