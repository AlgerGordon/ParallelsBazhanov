cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)


add_executable(PDP_test test_all.cpp
                        structure.ut.cpp
                        energy.ut.cpp
                        quantities.ut.cpp)

target_link_libraries(PDP_test test_runner)
target_link_libraries(PDP_test metallic_structures)
target_link_libraries(PDP_test tb_sma)


add_subdirectory(test_runner)
