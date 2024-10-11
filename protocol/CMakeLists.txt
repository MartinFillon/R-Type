cmake_minimum_required(VERSION 3.27)

add_library(protocol src/Packet.cpp)
target_include_directories(protocol PUBLIC include)
target_link_libraries(protocol ecs)

if(UNIX)
  add_compile_options(lX11)
endif()
