cmake_minimum_required(VERSION 3.16)

project(
  Chatoy
  VERSION 0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

include(CTest)
include(FetchContent)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
