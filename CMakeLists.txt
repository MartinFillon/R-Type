cmake_minimum_required(VERSION 3.27)
project(R-Type)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

add_subdirectory(ecs)
add_subdirectory(client)
add_subdirectory(server)

if(UNIX)
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

if(WIN32)
  add_compile_options(/Wall /W4)
endif()
