//
// Created by General on 01.12.2020.
//

#include <parameters.h>

Parameters& Parameters::operator+= (const Parameters& o) {
    for (int i = 0; i < PARAMETERS_SIZE; ++i ) {
        this->operator[](i) += o[i];
    }
    return *this;
}

Parameters operator+ (const Parameters& lhs, const Parameters& rhs) {
    return Parameters(
                lhs[R0_LOC] + rhs[R0_LOC],
                lhs[A0_LOC] + rhs[A0_LOC],
                lhs[A1_LOC] + rhs[A1_LOC],
                lhs[XI_LOC] + rhs[XI_LOC],
                lhs[P_LOC] + rhs[P_LOC],
                lhs[Q_LOC] + rhs[Q_LOC]
            );
}



