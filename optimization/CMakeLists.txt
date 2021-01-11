cmake_minimum_required(VERSION 3.17)
project(optimization)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall --std=c++1z -fopenmp")

FIND_PACKAGE(OpenMP)
    if(OPENMP_FOUND)
        message("OPENMP FOUND")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})

add_library(optimization nelder_mead.cpp losses.cpp tb_sma_optimization.cpp)
target_include_directories(optimization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(optimization tb_sma)
target_link_libraries(optimization ${OpenMP_CXX_LIBRARIES})