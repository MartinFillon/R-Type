cmake_minimum_required(VERSION 3.27)

add_library(size SHARED src/lib.cpp)
target_include_directories(size PRIVATE ../../include)
target_include_directories(size PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET size
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:size>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:size>)
