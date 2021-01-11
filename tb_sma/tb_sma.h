//
// Created by General on 17.11.2020.
//


#pragma once
#include <quantities.h>
#include <vector>
#include <omp.h>

MaterialQuantities computeMaterialQuantities(const Parameters& p, Structure& str, double def_rate);
AlloyQuantities computeAlloyQuantities(const InteractionParameters& aip,
                                        Structure& str,
                                        ATOM_ENUM alloy_type,
                                        double E_Acoh,
                                        size_t kAlloyAtomId = 54);

template<ZPERIOD zPeriodic>
double atomEnergy(const InteractionParameters& aip, const Structure& str,
                  int atomId,
                  const Matrix& deformation,
                  DEF_MATRICES_ENUM defType = NO_DEF) {

    Atom pivot_atom = str.lattice[atomId];
    Atom tmp_atom(pivot_atom.type());
    INTERACTION_ENUM cur_inter = BB;
    double repulsive_energy = 0, band_energy = 0;
    double r_ij;

    XYZ deformed_period = {1.0 * str.str_size, 1.0 * str.str_size, 1.0 * str.str_size};
    deformed_period *= deformation;
    double delta =  fmax(fmax(deformed_period[0], deformed_period[1]), deformed_period[2]);
    double cutoff = 1.7 * delta / str.str_size * str.lattice_constant;

    //#pragma omp parallel private(tmp_atom, cur_inter, r_ij) shared(str, atomId, cutoff, pivot_atom, deformation, defType, aip) default(none) reduction(+:repulsive_energy, band_energy) num_threads(4)
    {
        // std::cout << omp_get_num_threads() << '\n';
        // #pragma omp for schedule(static, 27)
        for (size_t j = 0; j < str.lattice.size(); j++) {
            if (atomId != j) {
                tmp_atom = str.lattice[j];
                if (pivot_atom.type() == tmp_atom.type()) {
                    cur_inter = pivot_atom.type() == str.base_type ? BB : AA;
                } else {
                    cur_inter = AB;
                }
                r_ij = minimizeDistance<zPeriodic>(pivot_atom, tmp_atom,
                                                    // str.period,
                                                   str.lattice_constant,
                                                   str.str_size,
                                                   deformation, defType);
                if (r_ij < cutoff) {
                    repulsive_energy +=
                            (aip[cur_inter][A1_LOC] *
                             (r_ij / aip[cur_inter][R0_LOC] - 1) +
                             aip[cur_inter][A0_LOC])
                            * exp(-aip[cur_inter][P_LOC] *
                                  (r_ij / aip[cur_inter][R0_LOC] - 1));
                    band_energy +=
                            aip[cur_inter][XI_LOC] * aip[cur_inter][XI_LOC]
                            * exp(-2 * aip[cur_inter][Q_LOC] *
                                  (r_ij / aip[cur_inter][R0_LOC] - 1));
                }
            }
        }
    }
    band_energy = -sqrt(band_energy);
    return (repulsive_energy + band_energy);
}

template<ZPERIOD zPeriodic>
double fullEnergy(const InteractionParameters& params, const Structure& str,
                  const Matrix& deformation,
                  DEF_MATRICES_ENUM defType = NO_DEF) {

    double energy = 0;
    #pragma omp parallel shared(std::cout, params, str, deformation, defType) default(none) reduction(+:energy) num_threads(8)
    {
        // std::cout << omp_get_num_threads() << '\n';
        #pragma omp for
        for (size_t i = 0; i < str.lattice.size(); ++i) {
            energy += atomEnergy<zPeriodic>(params, str, i, deformation, defType);
        }
    }
    return energy;
}

// Tests

void TestTB_SMA();
void TestAtomEnergy();
void TestInvTask();

