cmake_minimum_required(VERSION 3.27)

add_library(life SHARED src/lib.cpp)
target_include_directories(life PRIVATE ../../include)
target_include_directories(life PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET life
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:life>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:life>)
