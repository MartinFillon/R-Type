cmake_minimum_required(VERSION 3.27)

add_library(controllable SHARED src/lib.cpp)
target_include_directories(controllable PRIVATE ../../include)
target_include_directories(controllable PRIVATE ../../../protocol/include)
target_link_libraries(controllable PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET controllable
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:controllable>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:controllable>)
