cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-O3 -Wall --std=c++1z -fopenmp")

FIND_PACKAGE(OpenMP)
    if(OPENMP_FOUND)
        message("OPENMP FOUND")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})

add_executable(PDP_test test_all.cpp
                        structure.ut.cpp
                        energy.ut.cpp
                        material_quantities.ut.cpp
                        alloy_quantities.ut.cpp
                        inv_task.ut.cpp)

target_link_libraries(PDP_test test_runner)
target_link_libraries(PDP_test tb_sma)
target_link_libraries(PDP_test optimization)
target_link_libraries(PDP_test ${OpenMP_CXX_LIBRARIES})

add_subdirectory(test_runner)
