cmake_minimum_required(VERSION 3.27)

add_library(position SHARED src/lib.cpp)
target_include_directories(position PRIVATE ../../include)
target_include_directories(position PRIVATE ../../../protocol/include)
target_link_libraries(position PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET position
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:position>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:position>)
