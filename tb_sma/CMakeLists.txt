cmake_minimum_required(VERSION 3.17)
project(tb_sma)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-fopenmp -O3 -Wall --std=c++1z")

FIND_PACKAGE(OpenMP)
    if(OPENMP_FOUND)
        message("OPENMP FOUND")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})

add_library(tb_sma atom.h
                parameters.h parameters.cpp
                quantities.h quantities.cpp
                geometry.h geometry.cpp
                structure.h structure.cpp
                tb_sma.cpp)
target_include_directories(tb_sma PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

