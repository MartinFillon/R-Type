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

add_executable(r-type_client src/main.cpp src/Gui.cpp src/Network.cpp src/Packet.cpp src/TextureManager.cpp src/Menu.cpp src/GameClient.cpp)
target_link_libraries(r-type_client sfml-graphics)
target_link_directories(r-type_client PUBLIC ../ecs/include)
target_include_directories(r-type_client PUBLIC ../ecs/include include ../protocol)
target_link_libraries(r-type_client ecs)
target_link_libraries(r-type_client asio)
target_compile_features(r-type_client PRIVATE cxx_std_17)

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

if(UNIX)
  add_compile_options(lX11)
endif()
