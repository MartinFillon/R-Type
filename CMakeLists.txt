cmake_minimum_required(VERSION 3.27)
project(R-Type)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

add_subdirectory(ecs)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(protocol)
add_subdirectory(StreetFighter)

if(UNIX)
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

if(WIN32)
  add_compile_options(/Wall /W4)
endif()

if(UNIX)
  install(TARGETS r-type_server r-type_client RUNTIME DESTINATION bin)
  if(DEFINED ENV{XDG_CONFIG_HOME})
    install(DIRECTORY assets/ DESTINATION $ENV{XDG_CONFIG_HOME}/r-type/assets)
    install(DIRECTORY config/ DESTINATION $ENV{XDG_CONFIG_HOME}/r-type/config)
  else()
    install(DIRECTORY assets/ DESTINATION $ENV{HOME}/.config/r-type/assets)
    install(DIRECTORY config/ DESTINATION $ENV{HOME}/.config/r-type/config)
  endif()
endif()
include(CPack)

file(COPY config DESTINATION ${CMAKE_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
