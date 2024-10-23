include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)

FetchContent_MakeAvailable(raylib)
