cmake_minimum_required(VERSION 3.27)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_package(raylib REQUIRED)

add_executable(
  poc-raylib-3d
  src/Main.cpp
  src/Poc.cpp)

target_link_libraries(poc-raylib-3d -lraylib -lGL -lm -ldl -lrt -lX11 ecs)
target_link_directories(poc-raylib-3d PUBLIC include ../ecs/include ../protocol/include)
target_include_directories(poc-raylib-3d PUBLIC include ../ecs/include ../protocol/include)
target_compile_features(poc-raylib-3d PRIVATE cxx_std_17)

if(WIN32)
  add_custom_command(
    TARGET poc-raylib-3d
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:ecs>
    VERBATIM)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(poc-raylib-3d PRIVATE RELEASE=1)
endif()

if(UNIX)
  add_compile_options(lX11)
endif()

add_custom_command(
  TARGET poc-raylib-3d
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:poc-raylib-3d> ..)
