
#include "structure.h"
#include "tb_sma.h"
#include "test_runner.h"
#include <windows.h>

int main() {

    TestRunner tr;
    RUN_TEST(tr, TestMinimizeDist);
    std::cout.flush();
    std::cerr.flush();
    Sleep(200);
    RUN_TEST(tr, TestAtomEnergy);
    std::cout.flush();
    std::cerr.flush();
    Sleep(200);
    RUN_TEST(tr, TestMaterialQuantities);
    std::cout.flush();
    std::cerr.flush();
    Sleep(200);
    RUN_TEST(tr, TestAlloyQuantities);
    std::cout.flush();
    std::cerr.flush();


//    TestStructure();
//    std::cout.flush();
//    std::cerr.flush();
//    TestTB_SMA();
    return 0;
};