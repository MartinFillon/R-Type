cmake_minimum_required(VERSION 3.27)

add_library(planes SHARED src/lib.cpp)
target_include_directories(planes PRIVATE ../../include)
target_include_directories(planes PRIVATE ../../../protocol/include)
target_link_libraries(planes PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET planes
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:planes>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:planes>)
