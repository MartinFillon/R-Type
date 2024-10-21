cmake_minimum_required(VERSION 3.27)

add_library(hover SHARED src/lib.cpp)
target_include_directories(hover PRIVATE ../../include)
target_include_directories(hover PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET hover
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:hover>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:hover>)
