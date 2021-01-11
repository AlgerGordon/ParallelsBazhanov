cmake_minimum_required(VERSION 3.17)
project(ParallelDataProcessing)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall --std=c++1z -fopenmp")

add_executable(ParallelDataProcessing main.cpp)
target_link_libraries(ParallelDataProcessing tb_sma)
target_link_libraries(ParallelDataProcessing metallic_structures)
target_link_libraries(ParallelDataProcessing ${OpenMP_CXX_LIBRARIES})

add_subdirectory(tb_sma)
add_subdirectory(optimization)
add_subdirectory(test)




