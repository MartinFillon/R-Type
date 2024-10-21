cmake_minimum_required(VERSION 3.27)

add_library(filledcolor SHARED src/lib.cpp)
target_include_directories(filledcolor PRIVATE ../../include)
target_include_directories(filledcolor PRIVATE ../../../protocol/include)
target_link_libraries(filledcolor PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET filledcolor
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:filledcolor>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:filledcolor>)
