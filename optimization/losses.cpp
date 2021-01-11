//
// Created by General on 10.01.2021.
//


#include "optimization_methods.h"

double default_loss(const Quantities& tmp, const Quantities& target) {

//    double weights[9] = {1000, // lattice_constant
//                         500, // E_coh
//                         3, // B
//                         3, // C11
//                         3, // C12
//                         3, // C44
//                         2, // E_sol
//                         2, // E_dim_in
//                         2  // E_dim_on
//                         };
    double weights[9] = {100, // lattice_constant
                         100, // E_coh
                         10, // B
                         10, // C11
                         10, // C12
                         10, // C44
                         1, // E_sol
                         10, // E_dim_in
                         10  // E_dim_on
                         };
    double loss = 0;
    for (QUANTITIES_ENUM ind = LATTICE_CONSTANT_LOC; ind < QUANTITIES_SIZE;
            ind = static_cast<QUANTITIES_ENUM>(ind + 1))  {
//        loss += weights[ind] * (tmp[ind] - target[ind]) * (tmp[ind] - target[ind])
//                / (target[ind] * target[ind]);
        loss += weights[ind] * weights[ind] * (tmp[ind] - target[ind]) * (tmp[ind] - target[ind]);
    }
//    loss /= QUANTITIES_SIZE;
//    loss /= 1500;
    return sqrt(loss);
}
