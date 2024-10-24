include(FetchContent)

FetchContent_Declare(
  SpdLog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.14.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)

FetchContent_MakeAvailable(SpdLog)
