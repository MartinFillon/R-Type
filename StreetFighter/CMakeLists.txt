cmake_minimum_required(VERSION 3.27)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
  street-fighter
  src/Main.cpp
  src/StreetFighter.cpp)

target_link_libraries(street-fighter sfml-audio sfml-graphics ecs)
target_link_directories(street-fighter PUBLIC ../ecs/include)
target_include_directories(street-fighter PUBLIC include ../ecs/include
                                                         ../protocol/include)
target_compile_features(street-fighter PRIVATE cxx_std_17)

if(WIN32)
  add_custom_command(
    TARGET street-fighter
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:ecs>
    VERBATIM)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(street-fighter PRIVATE RELEASE=1)
endif()

if(UNIX)
  add_compile_options(lX11)
endif()

add_custom_command(
  TARGET street-fighter
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:street-fighter> ..)
