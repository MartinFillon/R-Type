cmake_minimum_required(VERSION 3.0)

project(R-Type)

set(CMAKE_CXX_STANDARD 14)

add_library(ecs STATIC ecs/lib.cpp)