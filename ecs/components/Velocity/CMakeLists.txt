cmake_minimum_required(VERSION 3.27)

add_library(velocity SHARED src/lib.cpp)
target_include_directories(velocity PRIVATE ../../include)
target_include_directories(velocity PRIVATE ../../../protocol/include)

add_custom_command(
  TARGET velocity
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:velocity>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:velocity>)
