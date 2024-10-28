cmake_minimum_required(VERSION 3.27)

add_library(color SHARED src/lib.cpp)
target_include_directories(color PRIVATE ../../include)
target_include_directories(color PRIVATE ../../../protocol/include)
target_link_libraries(color PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET color
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:color>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:color>)
