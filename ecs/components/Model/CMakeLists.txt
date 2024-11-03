cmake_minimum_required(VERSION 3.27)

add_library(model SHARED src/lib.cpp)
target_include_directories(model PRIVATE ../../include)
target_include_directories(model PRIVATE ../../../protocol/include)
target_link_libraries(model PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET model
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:model>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:model>)
