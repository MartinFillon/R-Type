cmake_minimum_required(VERSION 3.27)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_package(Sfml REQUIRED)
find_package(Asio REQUIRED)

add_executable(
  r-type_client
  src/Main.cpp
  src/Gui.cpp
  src/Network.cpp
  src/Menu.cpp
  src/Game.cpp
  src/RegistryWrapper.cpp)
target_link_libraries(r-type_client sfml-audio sfml-graphics)
target_link_directories(r-type_client PUBLIC ../ecs/include)
target_include_directories(r-type_client PUBLIC ../ecs/include include
                                                ../protocol/include)
target_link_libraries(r-type_client ecs)
target_link_libraries(r-type_client protocol)
target_link_libraries(r-type_client asio)
target_compile_features(r-type_client PRIVATE cxx_std_17)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(r-type_client PRIVATE RELEASE=1)
endif()

if(UNIX)
  add_compile_options(lX11)
endif()

add_custom_command(
  TARGET r-type_client
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ..)

if(WIN32)
  add_custom_command(
    TARGET r-type_client
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:ecs>
    VERBATIM)
endif()
