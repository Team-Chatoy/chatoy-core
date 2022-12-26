cmake_minimum_required(VERSION 3.16)

project(
  Chatoy
  VERSION 0.1
  LANGUAGES CXX
)

include(CTest)
include(FetchContent)

find_package(Boost REQUIRED)
# find_package(OpenSSL REQUIRED)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

add_subdirectory(src)
add_subdirectory(tests)
