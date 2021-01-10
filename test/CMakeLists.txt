cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-O3 -Wall --std=c++1z")

add_executable(PDP_test test_all.cpp
                        structure.ut.cpp
                        energy.ut.cpp
                        material_quantities.ut.cpp
                        alloy_quantities.ut.cpp
                        inv_task.ut.cpp)

target_link_libraries(PDP_test test_runner)
target_link_libraries(PDP_test metallic_structures)
target_link_libraries(PDP_test tb_sma)
target_link_libraries(PDP_test optimization)

add_subdirectory(test_runner)
