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

include(FetchContent)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(ecs src/Context.cpp src/ImageResolver.cpp src/ComponentFactory.cpp)
target_link_libraries(ecs PRIVATE sfml-graphics)
target_compile_features(ecs PRIVATE cxx_std_17)
target_include_directories(ecs PUBLIC include)
target_link_libraries(ecs PRIVATE nlohmann_json::nlohmann_json)

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

# option(ENABLE_TESTS "Build tests along with the library" ON)

if(ENABLE_TESTS)
  find_package(Criterion REQUIRED)

  enable_testing()
  add_executable(test_ecs test/ImageResolverTest.cpp)

  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

  target_link_libraries(test_ecs ecs ${CRITERION_LIBRARIES})

  # Enable a few warnings
  if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(test_ecs PRIVATE -Wall -Wextra)
  endif(CMAKE_COMPILER_IS_GNUCC)
  if(MSVC)
    target_compile_options(test_ecs PRIVATE /W4)
  endif(MSVC)

  add_test(test_ecs test_ecs)
endif()
