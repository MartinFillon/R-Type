cmake_minimum_required(VERSION 3.27)

add_library(invincibility SHARED src/lib.cpp)
target_include_directories(invincibility PRIVATE ../../include)
target_include_directories(invincibility PRIVATE ../../../protocol/include)
target_link_libraries(invincibility PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET invincibility
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:invincibility>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:invincibility>)
