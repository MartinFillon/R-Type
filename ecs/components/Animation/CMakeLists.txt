cmake_minimum_required(VERSION 3.27)

add_library(animations SHARED src/lib.cpp)
target_include_directories(animations PRIVATE ../../include)
target_include_directories(animations PRIVATE ../../../protocol/include)
target_link_libraries(animations PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET animations
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:animations>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:animations>)
