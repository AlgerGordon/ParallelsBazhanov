cmake_minimum_required(VERSION 3.17)
project(optimization)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-O3 -Wall --std=c++1z")

add_library(optimization nelder_mead.cpp losses.cpp)
target_include_directories(optimization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(optimization tb_sma)