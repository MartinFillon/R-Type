cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(R-Type)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(ecs)
add_subdirectory(client)
add_subdirectory(server)
