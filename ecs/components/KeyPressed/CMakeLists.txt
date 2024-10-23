cmake_minimum_required(VERSION 3.27)

add_library(key_pressed SHARED src/lib.cpp)
target_include_directories(key_pressed PRIVATE ../../include)
target_include_directories(key_pressed PRIVATE ../../../protocol/include)
target_link_libraries(key_pressed PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET key_pressed
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:key_pressed>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:key_pressed>)
