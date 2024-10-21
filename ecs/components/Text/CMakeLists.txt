cmake_minimum_required(VERSION 3.27)

add_library(text SHARED src/lib.cpp)
target_include_directories(text PRIVATE ../../include)
target_include_directories(text PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET text
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:text>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:text>)
