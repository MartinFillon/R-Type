cmake_minimum_required(VERSION 3.27)

add_library(rotate SHARED src/lib.cpp)
target_include_directories(rotate PRIVATE ../../include)
target_include_directories(rotate PRIVATE ../../../protocol/include)
target_link_libraries(rotate PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET rotate
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:rotate>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:rotate>)
