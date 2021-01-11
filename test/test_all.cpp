
#include "structure.h"
#include "tb_sma.h"
#include "test_runner.h"
#include <chrono>
#include <windows.h>

int main() {

    TestRunner tr;

    auto start = std::chrono::high_resolution_clock::now();

    RUN_TEST(tr, TestAtomEnergy);
    std::cout.flush();
    std::cerr.flush();
    Sleep(150);
    RUN_TEST(tr, TestMaterialQuantities);
    std::cout.flush();
    std::cerr.flush();
    Sleep(150);
    RUN_TEST(tr, TestAlloyQuantities);
    std::cout.flush();
    std::cerr.flush();

    Sleep(150);
    RUN_TEST(tr, TestQuantities);
    std::cout.flush();
    std::cerr.flush();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::chrono::seconds::period> elapsed_time = finish - start;

    std::cout << "Elapsed time for unit tests: " << elapsed_time.count() << 's' << endl;

    std::cout << "InvTask log: " << '\n';

    Sleep(150);
    RUN_TEST(tr, TestInvTask);
    std::cout.flush();
    std::cerr.flush();

    return 0;
};