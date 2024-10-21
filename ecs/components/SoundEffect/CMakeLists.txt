cmake_minimum_required(VERSION 3.27)

add_library(soundeffect SHARED src/lib.cpp)
target_include_directories(soundeffect PRIVATE ../../include)
target_include_directories(soundeffect PRIVATE ../../../protocol/include)
