cmake_minimum_required(VERSION 3.16)
project(test_runner)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall --std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_library(test_runner test_runner.cpp)
target_include_directories(test_runner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})