cmake_minimum_required(VERSION 3.10)

project(R-Type)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra)

add_executable(r-type_server
    src/Main.cpp
    src/Server.cpp
    src/Client.cpp
    src/Packet.cpp
    src/Game.cpp
)

target_include_directories(r-type_server PUBLIC include ../protocol)

include(FetchContent)

FetchContent_Declare(asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG        origin/master
)

set(ASIO_CMAKE_ASIO_TAG asio-1-12-2)
FetchContent_MakeAvailable(asio-cmake)

target_link_libraries(r-type_server
  PRIVATE asio
)
