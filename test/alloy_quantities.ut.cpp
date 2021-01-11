//
// Created by General on 10.01.2021.
//


#include <tb_sma.h>

void TestAlloyQuantities() {
    {

        double a0_cu = 3.6147;
        Structure str_cu;
        str_cu.createStructure(a0_cu, 3, ATOM_ENUM::CU);

        Parameters p_CuCu(2.556, 0.086, 0.0, 1.224, 10.960, 2.278);

        Parameters p_CoCo(2.378, 0.139, -0.852, 1.5247, 7.679, 2.139);

        Parameters p_CuCo(2.405, -0.049, -1.905, 0.7356, 8.183, 3.344);

        InteractionParameters aip(p_CuCu, p_CoCo, p_CuCo);

        double E_Acoh = -4.386;

        AlloyQuantities aq = computeAlloyQuantities(aip, str_cu, ATOM_ENUM::CO, E_Acoh);

        std::cout << "\nCo-Cu:" << '\n';
        std::cout << "Table E_sol: " << 0.4 << " Model: " << aq[A_E_SOL_LOC] << '\n';
        std::cout << "Table E_inDim: " << -0.26 << "(-0.35 fitted) " << " Model: " << aq[A_E_DIM_IN_LOC] << '\n';
        std::cout << "Table E_onDim: " << -1.04 << " Model: " << aq[A_E_DIM_ON_LOC] << '\n';


        char prev = std::cout.fill ('_');
        std::cout.width (40);
        std::cout << '\n';
        std::cout.fill(prev);
    }
}


void TestQuantities() {
    {

        double E_Acoh = -4.386;
        Quantities q(ATOM_ENUM::CU, ATOM_ENUM::CO, E_Acoh);

        double a0_cu = 3.6147;
        Structure str_cu;
        str_cu.createStructure(a0_cu, 3, ATOM_ENUM::CU);

        Parameters p_CuCu(2.556, 0.086, 0.0, 1.224, 10.960, 2.278);

        Parameters p_CoCo(2.378, 0.139, -0.852, 1.5247, 7.679, 2.139);

        Parameters p_CuCo(2.405, -0.049, -1.905, 0.7356, 8.183, 3.344);

        InteractionParameters aip(p_CuCu, p_CoCo, p_CuCo);

        q.computeQuantities(aip, str_cu);

        std::cout << "\nCu: " << '\n';
        std::cout << "Table E_coh: " << -3.544  << " Model: " <<  q[E_COH_LOC] << '\n';
        std::cout << "Table B: " << 1.42  << " Model: " <<  q[B_LOC] << '\n';
        std::cout << "Table C11: " << 1.76  << " Model: " <<  q[C11_LOC] << '\n';
        std::cout << "Table C12: " << 1.25  << " Model: " <<  q[C12_LOC] << '\n';
        std::cout << "Table C44: " << 0.82  << " Model: " <<  q[C44_LOC] << '\n';

        std::cout << "Table E_sol: " << 0.4 << " Model: " << q[E_SOL_LOC] << '\n';
        std::cout << "Table E_inDim: " << -0.26 << "(-0.35 fitted) " << " Model: " << q[E_DIM_IN_LOC] << '\n';
        std::cout << "Table E_onDim: " << -1.04 << " Model: " << q[E_DIM_ON_LOC] << '\n';


        char prev = std::cout.fill ('_');
        std::cout.width (40);
        std::cout << '\n';
        std::cout.fill(prev);
    }
}
