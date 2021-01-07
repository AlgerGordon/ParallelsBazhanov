//
// Created by General on 05.01.2021.
//

#include <tb_sma.h>

void TestMaterialQuantities() {
    {
        double a0 = 4.085;
        double r0 = a0 / sqrt(2) + 0.00001;;
        Parameters p(r0, 0.103, 0.0, 1.178, 10.928, 3.139);
        Structure str_ag_ag;
        createStructure<ATOM_ENUM::AG>(str_ag_ag, a0,
                                                            3, 3, 3);
        Matrix identity;
    }
    {
        double a0 = 3.61491;
        // a0 / sqrt(2) + 0.00001;
        double r0 = 2.55597;
        Parameters p(r0, 0.0855, 0.0, 1.224, 10.960, 2.278);
        Structure str_cu_cu;
        createStructure<ATOM_ENUM::CU>(str_cu_cu, a0,
                                                            3, 3, 3);
        double def_rate = 0.005;
        MaterialQuantities q = computeQuantities<ZPERIOD::Z_ON, MATERIAL_ENUM::CU>(p, str_cu_cu, def_rate);

        std::cout << "Cu: " << std::endl;
        std::cout << "Table E_coh: " << -3.544  << " Model: " <<  q[E_COH_LOC] << std::endl;
        std::cout << "Table B: " << 1.42  << " Model: " <<  q[B_LOC] << std::endl;
        std::cout << "Table C11: " << 1.76  << " Model: " <<  q[C11_LOC] << std::endl;
        std::cout << "Table C12: " << 1.25  << " Model: " <<  q[C12_LOC] << std::endl;
        std::cout << "Table C44: " << 0.82  << " Model: " <<  q[C44_LOC] << std::endl;

    }
    {
        double a0 = 4.085;
        double r0 = a0 / sqrt(2) + 0.00001;
        Parameters p(r0, 0.103, 0.0, 1.178, 10.928, 3.139);
        Structure str_ag_ag;
        createStructure<ATOM_ENUM::AG>(str_ag_ag, a0,
                                                            3, 3, 3);
        MaterialQuantities q = computeQuantities<ZPERIOD::Z_ON, MATERIAL_ENUM::AG>(p, str_ag_ag);

        std::cout << "Ag: " << std::endl;
        std::cout << "Table E_coh: " << -2.960  << " Model: " <<  q[E_COH_LOC] << std::endl;
        std::cout << "Table B: " << 1.08  << " Model: " <<  q[B_LOC] << std::endl;
        std::cout << "Table C11: " << 1.32 << " Model: " <<  q[C11_LOC] << std::endl;
        std::cout << "Table C12: " << 0.97 << " Model: " <<  q[C12_LOC] << std::endl;
        std::cout << "Table C44: " << 0.51 << " Model: " <<  q[C44_LOC] << std::endl;
    }
}