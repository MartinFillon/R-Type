cmake_minimum_required(VERSION 3.27)

add_library(shield SHARED src/lib.cpp)
target_include_directories(shield PRIVATE ../../include)
target_include_directories(shield PRIVATE ../../../protocol/include)
