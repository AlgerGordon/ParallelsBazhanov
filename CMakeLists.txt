cmake_minimum_required(VERSION 3.17)
project(ParallelDataProcessing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ParallelDataProcessing main.cpp)
target_link_libraries(ParallelDataProcessing tb_sma)
target_link_libraries(ParallelDataProcessing metallic_structures)

add_subdirectory(metallic_structures)
add_subdirectory(tb_sma)
add_subdirectory(test)




