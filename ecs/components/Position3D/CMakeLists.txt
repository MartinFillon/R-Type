cmake_minimum_required(VERSION 3.27)

add_library(position3d SHARED src/lib.cpp)
target_include_directories(position3d PRIVATE ../../include)
target_include_directories(position3d PRIVATE ../../../protocol/include)
target_link_libraries(position3d PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET position3d
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:position3d>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:position3d>)
