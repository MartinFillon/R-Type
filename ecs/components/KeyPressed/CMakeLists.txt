cmake_minimum_required(VERSION 3.27)

add_library(key SHARED src/lib.cpp)
target_include_directories(key PRIVATE ../../include)
target_include_directories(key PRIVATE ../../../protocol/include)
target_link_libraries(key PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET key
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:key>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:key>)
