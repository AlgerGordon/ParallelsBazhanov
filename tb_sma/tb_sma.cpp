//
// Created by General on 10.01.2021.
//


#include "tb_sma.h"

MaterialQuantities computeMaterialQuantities(const Parameters& p, Structure& str, double def_rate = 0.005){

    DefMatrices plus_def(def_rate);
    DefMatrices minus_def(-def_rate);

    double e_coh = atomEnergy<ZPERIOD::Z_ON>(p, str, 0, plus_def.to_vec_[NO_DEF]);

    const int kNumberOfAtoms = str.lattice.size();
    double e_equilibrium = e_coh * kNumberOfAtoms;

    double e_minus = 0, e_plus = 0;
    double v0 = str.str_size * str.str_size * str.str_size
                * str.lattice_constant * str.lattice_constant * str.lattice_constant;

    double magic_const = 0.8018993929636421;

    double B = 0;

    e_plus = fullEnergy<ZPERIOD::Z_ON>(p, str, plus_def.to_vec_[B_DEF], B_DEF);

    e_minus = fullEnergy<ZPERIOD::Z_ON>(p, str, minus_def.to_vec_[B_DEF], B_DEF);

    B = magic_const * 2 / (9 * v0) * (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    double e_c11_der = 0;

    e_plus = fullEnergy<ZPERIOD::Z_ON>(p, str,plus_def.to_vec_[C11_DEF], C11_DEF);

    e_minus = fullEnergy<ZPERIOD::Z_ON>(p, str, minus_def.to_vec_[C11_DEF], C11_DEF);

    e_c11_der = (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    double e_c12_der = 0;

    e_plus = fullEnergy<ZPERIOD::Z_ON>(p, str, plus_def.to_vec_[C12_DEF], C12_DEF);
    e_minus = fullEnergy<ZPERIOD::Z_ON>(p, str, minus_def.to_vec_[C12_DEF], C12_DEF);

    e_c12_der = (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    double C11 = magic_const / v0 * (e_c11_der + e_c12_der) / 2;
    double C12 = magic_const / v0 * (e_c11_der - e_c12_der) / 2;

    double C44 = 0;

    e_plus = fullEnergy<ZPERIOD::Z_ON>(p, str, plus_def.to_vec_[C44_DEF], C44_DEF);
    e_minus = fullEnergy<ZPERIOD::Z_ON>(p, str, minus_def.to_vec_[C44_DEF], C44_DEF);

//    std::cout << "E_eq: " << e_equilibrium << std::endl;
//    std::cout << "E_plus: " << e_plus << "\t E_minus: " << e_minus << std::endl;
//    std::cout << "V0: " << v0 << std::endl;

    C44 = magic_const / (2 * v0) * (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    return {e_coh, B, C11, C12, C44, str.base_type};
}

AlloyQuantities computeAlloyQuantities(const InteractionParameters& aip,
                                       Structure& str,
                                       ATOM_ENUM alloy_type,
                                       double E_Acoh,
                                       size_t kAlloyAtomId) {

    double E_Bcoh = atomEnergy<ZPERIOD::Z_ON>(aip, str, 0, {});
    double E_B = E_Bcoh * str.lattice.size();

    str.addAlloy(alloy_type, kAlloyAtomId);

    // double E_alloyed_atom = atomEnergy<ZPERIOD::Z_ON>(aip, str, kAlloyAtomId, {});

    double E_AB = fullEnergy<ZPERIOD::Z_ON>(aip, str, {});

    str.removeAlloy(kAlloyAtomId);

    double E_sol = E_AB - E_B - E_Acoh + E_Bcoh;

    str.removeAlloy(kAlloyAtomId);

    double E_surf = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    // Dimer in lattice

    str.addDimerIn(alloy_type);

    double E_dim_surf_in = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeFirstAtomOfDimerIn();

    double E_adatom_surf_in = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeSecondAtomOfDimerIn();

    double E_inDim = (E_dim_surf_in - E_surf) - 2 * (E_adatom_surf_in - E_surf);

    // Dimmer on lattice

    str.addDimerOn(alloy_type);

    double E_dim_surf_on = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeFirstAtomOfDimerOn();

    double E_adatom_surf_on = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeSecondAtomOfDimerOn();

    double E_onDim = (E_dim_surf_on - E_surf) - 2 * (E_adatom_surf_on - E_surf);

    return {E_sol, E_inDim, E_onDim, str.base_type, alloy_type};
}


void Quantities::computeQuantities(const InteractionParameters& aip,
                             Structure& str,
                             double def_rate,
                             size_t kAlloyAtomId) {

    DefMatrices plus_def(def_rate);
    DefMatrices minus_def(-def_rate);

    str.lattice_constant = aip[BB][R0_LOC] * sqrt(2);

    double E_Bcoh = atomEnergy<ZPERIOD::Z_ON>(aip, str, 0, plus_def.to_vec_[NO_DEF]);

    const int kNumberOfAtoms = str.lattice.size();
    double E_B = E_Bcoh * kNumberOfAtoms;

    double E_minus = 0, E_plus = 0;
    double v0 = str.str_size * str.str_size * str.str_size
                * str.lattice_constant * str.lattice_constant * str.lattice_constant;

    double magic_const = 0.8018993929636421;

    double B = 0;

    E_plus = fullEnergy<ZPERIOD::Z_ON>(aip, str, plus_def.to_vec_[B_DEF], B_DEF);

    E_minus = fullEnergy<ZPERIOD::Z_ON>(aip, str, minus_def.to_vec_[B_DEF], B_DEF);

    B = magic_const * 2 / (9 * v0) * (E_plus - 2 * E_B + E_minus) / (def_rate * def_rate);

    double e_c11_der = 0;

    E_plus = fullEnergy<ZPERIOD::Z_ON>(aip, str, plus_def.to_vec_[C11_DEF], C11_DEF);

    E_minus = fullEnergy<ZPERIOD::Z_ON>(aip, str, minus_def.to_vec_[C11_DEF], C11_DEF);

    e_c11_der = (E_plus - 2 * E_B + E_minus) / (def_rate * def_rate);

    double e_c12_der = 0;

    E_plus = fullEnergy<ZPERIOD::Z_ON>(aip, str, plus_def.to_vec_[C12_DEF], C12_DEF);
    E_minus = fullEnergy<ZPERIOD::Z_ON>(aip, str, minus_def.to_vec_[C12_DEF], C12_DEF);

    e_c12_der = (E_plus - 2 * E_B + E_minus) / (def_rate * def_rate);

    double C11 = magic_const / v0 * (e_c11_der + e_c12_der) / 2;
    double C12 = magic_const / v0 * (e_c11_der - e_c12_der) / 2;

    double C44 = 0;

    E_plus = fullEnergy<ZPERIOD::Z_ON>(aip, str, plus_def.to_vec_[C44_DEF], C44_DEF);
    E_minus = fullEnergy<ZPERIOD::Z_ON>(aip, str, minus_def.to_vec_[C44_DEF], C44_DEF);

//    std::cout << "E_eq: " << e_equilibrium << std::endl;
//    std::cout << "E_plus: " << e_plus << "\t E_minus: " << e_minus << std::endl;
//    std::cout << "V0: " << v0 << std::endl;

    C44 = magic_const / (2 * v0) * (E_plus - 2 * E_B + E_minus) / (def_rate * def_rate);


    str.addAlloy(alloy_type_, kAlloyAtomId);

    // double E_alloyed_atom = atomEnergy<ZPERIOD::Z_ON>(aip, str, kAlloyAtomId, {});

    double E_AB = fullEnergy<ZPERIOD::Z_ON>(aip, str, {});

    str.removeAlloy(kAlloyAtomId);

    double E_sol = E_AB - E_B - E_Acoh_ + E_Bcoh;

    str.removeAlloy(kAlloyAtomId);

    double E_surf = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    // Dimer in lattice

    str.addDimerIn(alloy_type_);

    double E_dim_surf_in = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeFirstAtomOfDimerIn();

    double E_adatom_surf_in = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeSecondAtomOfDimerIn();

    double E_inDim = (E_dim_surf_in - E_surf) - 2 * (E_adatom_surf_in - E_surf);

    // Dimmer on lattice

    str.addDimerOn(alloy_type_);

    double E_dim_surf_on = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeFirstAtomOfDimerOn();

    double E_adatom_surf_on = fullEnergy<ZPERIOD::Z_OFF>(aip, str, {});

    str.removeSecondAtomOfDimerOn();

    double E_onDim = (E_dim_surf_on - E_surf) - 2 * (E_adatom_surf_on - E_surf);

    q_[LATTICE_CONSTANT_LOC] = str.lattice_constant,
    q_[E_COH_LOC] = E_Bcoh;
    q_[B_LOC] = B;
    q_[C11_LOC] = C11;
    q_[C12_LOC] = C12;
    q_[C44_LOC] = C44;
    q_[E_SOL_LOC] = E_sol;
    q_[E_DIM_IN_LOC] = E_inDim;
    q_[E_DIM_ON_LOC] = E_onDim;
}