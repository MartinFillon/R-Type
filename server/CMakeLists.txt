cmake_minimum_required(VERSION 3.28)
project(R-Type-Server LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(r-type_server src/main.cpp)
target_link_libraries(r-type_server PRIVATE sfml-graphics)
target_link_directories(r-type_client PRIVATE ../ecs)
target_link_libraries(r-type_client ecs)
target_compile_features(r-type_server PRIVATE cxx_std_17)

if(WIN32)
  add_custom_command(
    TARGET r-type_server
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:ecs>
    VERBATIM)
endif()

add_custom_command(
  TARGET r-type_server
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ..)
