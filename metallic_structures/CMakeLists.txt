cmake_minimum_required(VERSION 3.17)
project(metallic_structures)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-O3 -Wall --std=c++1z")

add_library(metallic_structures atom.h
                                quantities.h quantities.cpp
                                geometry.h geometry.cpp
                                structure.h structure.cpp)
target_include_directories(metallic_structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})