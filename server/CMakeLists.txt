cmake_minimum_required(VERSION 3.27)

add_executable(r-type_server src/Main.cpp src/Server.cpp src/Client.cpp
                             src/Game.cpp src/Context.cpp src/Network.cpp)

target_include_directories(r-type_server PUBLIC include ../protocol/include
                                                ../ecs/include)

include(FetchContent)

FetchContent_Declare(
  asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG origin/master)

set(ASIO_CMAKE_ASIO_TAG asio-1-12-2)
FetchContent_MakeAvailable(asio-cmake)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

target_link_libraries(r-type_server PRIVATE ecs)
target_link_libraries(r-type_server PRIVATE protocol)
target_link_libraries(r-type_server PRIVATE asio)

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
