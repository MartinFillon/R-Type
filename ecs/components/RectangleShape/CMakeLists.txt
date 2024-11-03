cmake_minimum_required(VERSION 3.27)

add_library(rectangle SHARED src/lib.cpp)
target_include_directories(rectangle PRIVATE ../../include)
target_include_directories(rectangle PRIVATE ../../../protocol/include)
target_link_libraries(rectangle PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET rectangle
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:rectangle>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:rectangle>)
