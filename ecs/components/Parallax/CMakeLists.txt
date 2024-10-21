cmake_minimum_required(VERSION 3.27)

add_library(parallax SHARED src/lib.cpp)
target_include_directories(parallax PRIVATE ../../include)
target_include_directories(parallax PRIVATE ../../../protocol/include)
target_link_libraries(parallax PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET parallax
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:parallax>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:parallax>)
