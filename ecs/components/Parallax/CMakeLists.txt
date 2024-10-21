cmake_minimum_required(VERSION 3.27)

add_library(parallax SHARED src/lib.cpp)
target_include_directories(parallax PRIVATE ../../include)
target_include_directories(parallax PRIVATE ../../../protocol/include)
