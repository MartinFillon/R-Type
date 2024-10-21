cmake_minimum_required(VERSION 3.27)

add_library(outlinedcolor SHARED src/lib.cpp)
target_include_directories(outlinedcolor PRIVATE ../../include)
target_include_directories(outlinedcolor PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET outlinedcolor
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:outlinedcolor>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:outlinedcolor>)
