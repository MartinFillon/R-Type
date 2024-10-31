cmake_minimum_required(VERSION 3.27)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_package(Json REQUIRED)
find_package(SpdLog REQUIRED)
find_package(JsonSchemaValidator REQUIRED)
find_package(Dylib REQUIRED)

add_subdirectory(components)

add_library(
  ecs
  src/ComponentFactory.cpp
  src/systems/BasicRandomEnnemiesSystem.cpp
  src/systems/BossSystems.cpp
  src/systems/CollisionsSystem.cpp
  src/systems/DestroySystem.cpp
  src/systems/BossSystems.cpp
  src/systems/CollisionsSystem.cpp
  src/systems/GravitableMouvementSystem.cpp
  src/systems/PunchSystem.cpp
  src/systems/KickSystem.cpp
  src/systems/CinematicsSystem.cpp
  src/systems/BasicMouvementSystem.cpp
  src/systems/EnnemiesMilepatesSystem.cpp
  src/systems/ParallaxSystem.cpp
  src/systems/GunFireSystem.cpp
  src/systems/InvincibilitySystem.cpp
  src/Registry.cpp
  src/Utils.cpp
  src/SystemsManager.cpp)
target_compile_features(ecs PRIVATE cxx_std_17)
target_include_directories(ecs PUBLIC include ../protocol/include)
target_link_libraries(ecs PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(ecs PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
target_link_libraries(ecs PUBLIC nlohmann_json_schema_validator)
target_link_libraries(ecs PUBLIC dylib)

option(ENABLE_TESTS "Build tests along with the library" OFF)

if(ENABLE_TESTS AND UNIX)
  find_package(Criterion REQUIRED)

  enable_testing()
  add_executable(test_ecs test/EntityTest.cpp test/EntityManagerTest.cpp
                          test/ZipperIteratorTest.cpp)

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
