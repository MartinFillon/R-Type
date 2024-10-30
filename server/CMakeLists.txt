cmake_minimum_required(VERSION 3.27)

add_executable(r-type_server src/Main.cpp src/Server.cpp src/Client.cpp
                             src/Game.cpp src/Context.cpp)

target_include_directories(r-type_server PUBLIC include ../protocol/include
                                                ../ecs/include)

find_package(Asio REQUIRED)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

target_link_libraries(r-type_server PRIVATE ecs)
target_link_libraries(r-type_server PRIVATE protocol)
target_link_libraries(r-type_server PRIVATE asio)

add_custom_command(
  TARGET r-type_server
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ..)
