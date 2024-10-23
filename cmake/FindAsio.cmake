include(FetchContent)

FetchContent_Declare(
  asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG origin/master)

set(ASIO_CMAKE_ASIO_TAG asio-1-12-2)
FetchContent_MakeAvailable(asio-cmake)
