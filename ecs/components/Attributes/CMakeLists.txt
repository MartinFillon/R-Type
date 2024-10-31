cmake_minimum_required(VERSION 3.27)

add_library(attributes SHARED src/lib.cpp)
target_include_directories(attributes PRIVATE ../../include)
target_include_directories(attributes PRIVATE ../../../protocol/include)
target_link_libraries(attributes PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET attributes
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:attributes>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:attributes>)
