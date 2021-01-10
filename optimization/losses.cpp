//
// Created by General on 10.01.2021.
//


#include "optimization_methods.h"

double default_loss(const Quantities& tmp, const Quantities& target) {
    // lattice_constant, E_coh,
    //                B,
    //                C11,
    //                C12,
    //                C44,
    //               E_sol,
    //                E_dim_in,
    //                E_dim_on,
    double weights[9] = {10, // lattice_constant
                         3, // E_coh
                         3, // B
                         3, // C11
                         3, // C12
                         3, // C44
                         2, // E_sol
                         2, // E_dim_in
                         2  // E_dim_on
                         };
    double loss = 0;
    for (QUANTITIES_ENUM ind = LATTICE_CONSTANT_LOC; ind < QUANTITIES_SIZE;
            ind = static_cast<QUANTITIES_ENUM>(ind + 1))  {
        loss += weights[ind] * (tmp[ind] - target[ind]) * (tmp[ind] - target[ind])
                / (target[ind] * target[ind]);
    }
    loss /= QUANTITIES_SIZE;
    return sqrt(loss);
}
