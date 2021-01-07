//
// Created by General on 17.11.2020.
//


#pragma once
#include <structure.h>
#include <parameters.h>
#include <atom.h>
#include <vector>


template<ZPERIOD zPeriodic>
double atomEnergy(const Parameters& p, const Lattice& lattice, int atomId,
                  const XYZ& period,
                  const Matrix& deformation,
                  DEF_MATRICES_ENUM defType = NO_DEF) {

//    if (defMatrix != NO_DEF) {
//        lattice *= deformation;
//        //period *= deformation;
//    }

    XYZ pivot_atom_pos = lattice[atomId].pos();
    XYZ tmp_atom_pos;
    double repulsive_energy = 0, band_energy = 0, r_ij;


    XYZ deformed_period = deformation * period;
    // TODO: replace /3 на size из structure
    double cutoff = 1.7 * fmax(fmax(deformed_period[0], deformed_period[1]), deformed_period[2]) / 3;

    int count = 0;

    for (size_t j = 0; j < lattice.size(); ++j) {
        if (atomId != j) {
            tmp_atom_pos = lattice[j].pos();
            r_ij = minimizeDistance<zPeriodic>(pivot_atom_pos, tmp_atom_pos, period, deformation, defType);
            if (r_ij < cutoff) {
                // std::cout << r_ij << std::endl;
                count += 1;
                repulsive_energy +=
                        (p[A1_LOC] * (r_ij - p[R0_LOC]) + p[A0_LOC])
                        * exp(-p[P_LOC] * (r_ij/p[R0_LOC] - 1));
                band_energy += p[XI_LOC] * p[XI_LOC]
                        * exp(-2 * p[Q_LOC] * (r_ij/p[R0_LOC] - 1));
            }
        }
    }
    band_energy = -sqrt(band_energy);
    // std::cout << "Count: " << count << std::endl;
    // std::cout << "Energies: " << repulsive_energy << ' ' << band_energy << std::endl;
    return (repulsive_energy + band_energy);
}

template<ZPERIOD zPeriodic>
double fullEnergy(const Parameters& params, const Structure& str, const Matrix& deformation, DEF_MATRICES_ENUM defType = NO_DEF) {
    double energy = 0;

    Matrix identity;
    for(size_t i = 0; i < str.lattice.size(); ++i){
        energy += atomEnergy<zPeriodic>(params, str.lattice, i, str.period, deformation, defType);
    }
    return energy;
}

template<ZPERIOD zPeriodic, MATERIAL_ENUM material>
MaterialQuantities computeQuantities(const Parameters& p, Structure& str, double def_rate = 0.01){
    const int kNumberOfAtoms = str.lattice.size();
    constexpr int kAtomId = 55;

    DefMatrices plus_def(def_rate);
    DefMatrices minus_def(-def_rate);
    double e_coh = atomEnergy<zPeriodic>(
            p, str.lattice, 0, str.period, plus_def.to_vec_[NO_DEF]);

    double e_equilibrium = e_coh * kNumberOfAtoms;

    double e_minus = 0, e_plus = 0;
    double v0 = str.period[0] * str.period[1] * str.period[2];

    double magic_const = 0.8018993929636421;

    double B = 0;

    e_plus = kNumberOfAtoms * atomEnergy<zPeriodic>(
            p, str.lattice, kAtomId, str.period, plus_def.to_vec_[B_DEF], B_DEF);

    e_minus = kNumberOfAtoms * atomEnergy<zPeriodic>(
            p, str.lattice, kAtomId, str.period, minus_def.to_vec_[B_DEF], B_DEF);

    B = magic_const * 2 / (9 * v0) * (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    double e_c11_der = 0;

    e_plus = kNumberOfAtoms * atomEnergy<zPeriodic>(
            p, str.lattice, kAtomId, str.period, plus_def.to_vec_[C11_DEF], C11_DEF);

    e_minus = kNumberOfAtoms * atomEnergy<zPeriodic>(
            p, str.lattice, kAtomId, str.period, minus_def.to_vec_[C11_DEF], C11_DEF);

    e_c11_der = (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    double e_c12_der = 0;

    e_plus = kNumberOfAtoms * atomEnergy<zPeriodic>(
            p, str.lattice, kAtomId, str.period, plus_def.to_vec_[C12_DEF], C12_DEF);
    e_minus = kNumberOfAtoms * atomEnergy<zPeriodic>(
            p, str.lattice, kAtomId, str.period, minus_def.to_vec_[C12_DEF], C12_DEF);

    e_c12_der = (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    double C11 = magic_const / v0 * (e_c11_der + e_c12_der) / 2;
    double C12 = magic_const / v0 * (e_c11_der - e_c12_der) / 2;

    double C44 = 0;

    e_plus = fullEnergy<zPeriodic>(p, str, plus_def.to_vec_[C44_DEF], C44_DEF);
    e_minus = fullEnergy<zPeriodic>(p, str, minus_def.to_vec_[C44_DEF], C44_DEF);

    std::cout << "E_eq: " << e_equilibrium << std::endl;
    std::cout << "E_plus: " << e_plus << "\t E_minus: " << e_minus << std::endl;
    std::cout << "V0: " << v0 << std::endl;
    C44 = magic_const / (2 * v0) * (e_plus - 2 * e_equilibrium + e_minus) / (def_rate * def_rate);

    return {e_coh, B, C11, C12, C44, material};
}

// Tests

void TestTB_SMA();
void TestAtomEnergy();
void TestMaterialQuantities();

