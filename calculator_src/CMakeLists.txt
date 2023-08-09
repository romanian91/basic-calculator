cmake_minimum_required (VERSION 2.8)

project (calculator)

# GTest

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_BUILD_TYPE Release)

include_directories(include)
file(GLOB SOURCES "sources/*.cpp")

add_executable( calculator ${SOURCES})
