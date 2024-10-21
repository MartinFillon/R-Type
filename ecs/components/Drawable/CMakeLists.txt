cmake_minimum_required(VERSION 3.27)

add_library(drawable SHARED src/lib.cpp)
target_include_directories(drawable PRIVATE ../../include)
target_include_directories(drawable PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET drawable
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:drawable>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:drawable>)
