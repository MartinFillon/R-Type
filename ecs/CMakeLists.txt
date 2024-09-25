cmake_minimum_required(VERSION 3.28)
project(R-Type-ECS LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(ecs src/Context.cpp src/ImageResolver.cpp)
target_link_libraries(ecs PRIVATE sfml-graphics)
target_compile_features(ecs PRIVATE cxx_std_17)
target_include_directories(ecs PUBLIC include)

if(WIN32)
  add_custom_command(
    TARGET ecs
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:ecs>
    VERBATIM)
endif()
