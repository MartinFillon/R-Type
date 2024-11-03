cmake_minimum_required(VERSION 3.27)

add_library(animation3d SHARED src/lib.cpp)
target_include_directories(animation3d PRIVATE ../../include)
target_include_directories(animation3d PRIVATE ../../../protocol/include)
target_link_libraries(animation3d PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET animation3d
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:animation3d>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:animation3d>)
