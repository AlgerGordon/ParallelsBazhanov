//
// Created by General on 05.12.2020.
//

#include <tb_sma.h>
#include <test_runner.h>

void TestAtomEnergy() {
    {
        double a0 = 4.085;
        double r0 = a0 / sqrt(2) + 0.00001;
        Parameters p(r0, 0.103, 0.0, 1.178, 10.928, 3.139);
        Structure str_ag_ag;
        createStructure<ATOM_ENUM::AG>(str_ag_ag, a0,
                                                            3, 3, 3);
        Matrix identity;
        double atom_energy = atomEnergy<ZPERIOD::Z_ON>(
                p, str_ag_ag.lattice, 57, str_ag_ag.period, identity);
        std::cout << "Ag:" << std::endl;
        std::cout << "Table: " << -2.960  << " Model: " << atom_energy << std::endl;
    }
    {
        double a0 = 3.6147;
        double r0 = a0 / sqrt(2) + 0.00001;;
        Parameters p(r0, 0.0855, 0.0, 1.224, 10.960, 2.278);
        Structure str_cu_cu;
        createStructure<ATOM_ENUM::CU>(str_cu_cu, a0,
                                                            3, 3, 3);
        Matrix identity;
        double atom_energy = atomEnergy<ZPERIOD::Z_ON>(
                p, str_cu_cu.lattice, 0, str_cu_cu.period, identity);

        double e0 = 0;
//        for (int atomId = 0; atomId < str_cu_cu.lattice.size(); ++atomId) {
//            e0 +=  atomEnergy<ZPERIOD::Z_ON, NO_DEF>(
//                    p, str_cu_cu.lattice, atomId, str_cu_cu.period, identity);
//        }

        char prev = std::cout.fill ('_');
        std::cout.width (40);
        std::cout << '\n';
        std::cout.fill(prev);

        std::cout << "Cu:" << std::endl;
        std::cout << "Table: " << -3.544  << " Model: " << atom_energy << std::endl;

    }
    {
//        a0 = 4.02922
//        A0 = 0.105651
//        A1 = 0.010198
//        p = 10.8674
//        q = 3.09243
//        ksi = 1.17051
//        r0 = 2.84909
        double a0 = 4.02922;
        double r0 =  a0 / sqrt(2)  * (1 + 1e-6);
        Parameters p(r0, 0.105651, 0.010198, 1.17051, 10.8674, 3.09243);
        Structure str_cu_cu;
        createStructure<ATOM_ENUM::AG>(str_cu_cu, a0,
                                                            3, 3, 3);
        Matrix identity;
        double atom_energy = atomEnergy<ZPERIOD::Z_ON>(
                p, str_cu_cu.lattice, 24, str_cu_cu.period, identity);

        char prev = std::cout.fill ('_');
        std::cout.width (40);
        std::cout << '\n';
        std::cout.fill(prev);

        std::cout << "Ag_1:" << std::endl;
        std::cout << "Table: " << -2.9042 << " Model: " << atom_energy << std::endl;
    }
}



void TestTB_SMA() {
    TestRunner tr;
    RUN_TEST(tr, TestAtomEnergy);
    RUN_TEST(tr, TestMaterialQuantities);
}
