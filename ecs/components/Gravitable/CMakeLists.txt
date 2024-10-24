cmake_minimum_required(VERSION 3.27)

add_library(gravitable SHARED src/lib.cpp)
target_include_directories(gravitable PRIVATE ../../include)
target_include_directories(gravitable PRIVATE ../../../protocol/include)
target_link_libraries(gravitable PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET gravitable
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gravitable>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:gravitable>)
