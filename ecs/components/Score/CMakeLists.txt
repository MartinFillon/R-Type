cmake_minimum_required(VERSION 3.27)

add_library(score SHARED src/lib.cpp)
target_include_directories(score PRIVATE ../../include)
target_include_directories(score PRIVATE ../../../protocol/include)
target_link_libraries(score PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET score
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:score>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:score>)
