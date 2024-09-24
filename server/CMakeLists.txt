cmake_minimum_required(VERSION 3.10)

project(R-Type)

add_compile_options(-Wall -Wextra)

set(CMAKE_CXX_STANDARD 14)

add_executable(r-type_server
    src/Main.cpp
    src/Server.cpp
    src/Client.cpp
)

target_include_directories(r-type_server PUBLIC include)
