//
// Created by General on 05.01.2021.
//

#include <tb_sma.h>

void TestMaterialQuantities() {
    {
        double a0 = 3.61491;
        // a0 / sqrt(2) + 0.00001;
        double r0 = 2.55597;
        Parameters p(r0, 0.0855, 0.0, 1.224, 10.960, 2.278);
        Structure str_cu_cu;
        str_cu_cu.createStructure(a0, 3, ATOM_ENUM::CU);
        double def_rate = 0.005;
        MaterialQuantities q = computeMaterialQuantities(p, str_cu_cu, def_rate);

        std::cout << "\nCu: " << '\n';
        std::cout << "Table E_coh: " << -3.544  << " Model: " <<  q[M_E_COH_LOC] << '\n';
        std::cout << "Table B: " << 1.42  << " Model: " <<  q[M_B_LOC] << '\n';
        std::cout << "Table C11: " << 1.76  << " Model: " <<  q[M_C11_LOC] << '\n';
        std::cout << "Table C12: " << 1.25  << " Model: " <<  q[M_C12_LOC] << '\n';
        std::cout << "Table C44: " << 0.82  << " Model: " <<  q[M_C44_LOC] << '\n';

        char prev = std::cout.fill ('_');
        std::cout.width (40);
        std::cout << '\n';
        std::cout.fill(prev);
    }
    {
        double a0 = 4.085;
        double r0 = a0 / sqrt(2) + 0.00001;
        Parameters p(r0, 0.103, 0.0, 1.178, 10.928, 3.139);
        Structure str_ag_ag;
        str_ag_ag.createStructure(a0, 3, ATOM_ENUM::AG);

        double def_rate = 0.005;
        MaterialQuantities q = computeMaterialQuantities(p, str_ag_ag, def_rate);

        std::cout << "\nAg: " << '\n';
        std::cout << "Table E_coh: " << -2.960  << " Model: " <<  q[M_E_COH_LOC] << '\n';
        std::cout << "Table B: " << 1.08  << " Model: " <<  q[M_B_LOC] << '\n';
        std::cout << "Table C11: " << 1.32 << " Model: " <<  q[M_C11_LOC] << '\n';
        std::cout << "Table C12: " << 0.97 << " Model: " <<  q[M_C12_LOC] << '\n';
        std::cout << "Table C44: " << 0.51 << " Model: " <<  q[M_C44_LOC] << '\n';

        char prev = std::cout.fill ('_');
        std::cout.width (40);
        std::cout << '\n';
        std::cout.fill(prev);
    }
}