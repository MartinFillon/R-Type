cmake_minimum_required(VERSION 3.27)

add_library(sprite SHARED src/lib.cpp)
target_include_directories(sprite PRIVATE ../../include)
target_include_directories(sprite PRIVATE ../../../protocol/include)
target_link_libraries(sprite PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET sprite
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sprite>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:sprite>)
