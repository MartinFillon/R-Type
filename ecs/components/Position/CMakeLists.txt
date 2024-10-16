cmake_minimum_required(VERSION 3.27)

add_library(position SHARED src/lib.cpp)
target_include_directories(position PRIVATE ../../include)
target_include_directories(position PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET position
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:position> ..)
