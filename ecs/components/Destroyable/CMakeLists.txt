cmake_minimum_required(VERSION 3.27)

add_library(destroyable SHARED src/lib.cpp)
target_include_directories(destroyable PRIVATE ../../include)
target_include_directories(destroyable PRIVATE ../../../protocol/include)
target_link_libraries(destroyable PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET destroyable
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:destroyable>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:destroyable>)
