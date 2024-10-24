cmake_minimum_required(VERSION 3.27)

add_library(soundeffect SHARED src/lib.cpp)
target_include_directories(soundeffect PRIVATE ../../include)
target_include_directories(soundeffect PRIVATE ../../../protocol/include)
target_link_libraries(soundeffect PUBLIC nlohmann_json::nlohmann_json)

add_custom_command(
  TARGET soundeffect
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:soundeffect>
          ${CMAKE_BINARY_DIR}/components/$<TARGET_FILE_NAME:soundeffect>)
