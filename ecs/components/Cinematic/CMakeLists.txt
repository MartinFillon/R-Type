cmake_minimum_required(VERSION 3.27)

add_library(cinematic SHARED src/lib.cpp)
target_include_directories(cinematic PRIVATE ../../include)
target_include_directories(cinematic PRIVATE ../../../protocol/include)
target_link_libraries(cinematic PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET cinematic
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:cinematic>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:cinematic>)
