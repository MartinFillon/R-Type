cmake_minimum_required(VERSION 3.27)

add_library(animation SHARED src/lib.cpp)
target_include_directories(animation PRIVATE ../../include)
target_include_directories(animation PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET animation
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:animation>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:animation>)
