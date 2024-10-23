include(FetchContent)

FetchContent_Declare(
  JsonSchemaValidator
  GIT_REPOSITORY https://github.com/pboettch/json-schema-validator
  GIT_TAG 2.3.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)

FetchContent_MakeAvailable(JsonSchemaValidator)
