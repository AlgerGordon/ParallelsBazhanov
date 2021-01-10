cmake_minimum_required(VERSION 3.17)
project(tb_sma)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-O3 -Wall --std=c++1z")

add_library(tb_sma parameters.cpp tb_sma.cpp)
target_include_directories(tb_sma PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tb_sma metallic_structures)