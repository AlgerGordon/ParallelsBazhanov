//
// Created by General on 07.12.2020.
//


#include "structure.h"

void operator *= (Lattice& l, const Matrix& m) {
    for (Atom& item : l) {
        item *= m;
    }
}

DefMatrices::DefMatrices(double delta) {
    to_vec_.resize(DEF_MATR_SIZE);
    double diag[3];
    // NO_DEF: set by default
    // B
    diag[0] = 1 + delta; diag[1] = 1 + delta; diag[2] = 1 + delta;
    to_vec_[B_DEF].setDiagonal(diag);
    // C11
    diag[0] = 1 + delta; diag[1] = 1 + delta; diag[2] = 1;
    to_vec_[C11_DEF].setDiagonal(diag);
    // C12
    diag[0] = 1 + delta; diag[1] = 1 - delta; diag[2] = 1;
    to_vec_[C12_DEF].setDiagonal(diag);
    // C44
    diag[0] = 1; diag[1] = 1; diag[2] = 1 / (1 - delta * delta);
    to_vec_[C44_DEF].setDiagonal(diag);
    to_vec_[C44_DEF][0][1] = delta;
    to_vec_[C44_DEF][1][0] = delta;
}