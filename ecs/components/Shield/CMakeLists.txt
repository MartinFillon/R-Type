cmake_minimum_required(VERSION 3.27)

add_library(shield SHARED src/lib.cpp)
target_include_directories(shield PRIVATE ../../include)
target_include_directories(shield PRIVATE ../../../protocol/include)
target_link_libraries(shield PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET shield
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:shield>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:shield>)
