//
// Created by General on 07.12.2020.
//


#include "structure.h"

void Structure::createStructure(double lattice_const, int new_size, ATOM_ENUM a_type) {
    this->lattice = {};
    this->lattice_constant = lattice_const;
    this->str_size = new_size;
    this->base_type = a_type;

    for (int i = 0; i < str_size; ++i) {
        for (int j = 0; j < str_size; ++j) {
            for (int k = 0; k < str_size; ++k) {
                this->lattice.emplace_back(Atom(a_type, (0 + i), (0 + j),
                                                (0 + k)));
                this->lattice.emplace_back(Atom(a_type, (0.5 + i), (0.5 + j),
                                                (0 + k)));
                this->lattice.emplace_back(Atom(a_type, (0 + i), (0.5 + j),
                                                (0.5 + k)));
                this->lattice.emplace_back(Atom(a_type, (0.5 + i), (0 + j),
                                                (0.5 + k)));
            }
        }
    }
}

void Structure::addAlloy(ATOM_ENUM a_type, size_t ind) {
    lattice[ind].set_type(a_type);
}

void Structure::removeAlloy(size_t ind) {
    lattice[ind].set_type(base_type);
}

void Structure::addDimerIn(ATOM_ENUM a_type) {
    size_t kAtomInd1 = (str_size - 1) * 4 + 2;
    size_t kAtomInd2 = (str_size - 1) * 4 + 3;
    lattice[kAtomInd1].set_type(a_type);
    lattice[kAtomInd2].set_type(a_type);
}

void Structure::removeFirstAtomOfDimerIn() {
    size_t kAtomInd1 = (str_size - 1) * 4 + 2;
    lattice[kAtomInd1].set_type(base_type);
}

void Structure::removeSecondAtomOfDimerIn() {
    size_t kAtomInd2 = (str_size - 1) * 4 + 3;
    lattice[kAtomInd2].set_type(base_type);
}

void Structure::addDimerOn(ATOM_ENUM a_type) {
    XYZ tmp_pos = {0, 0, 1.0 * str_size};
    XYZ pos1 = lattice[0].pos() + tmp_pos;
    XYZ pos2 = lattice[1].pos() + tmp_pos;
    lattice.push_back(Atom(a_type, pos1));
    lattice.push_back(Atom(a_type, pos2));
}

bool Structure::removeFirstAtomOfDimerOn() {
    if (lattice.size() != 4 * str_size * str_size * str_size) {
        lattice.pop_back();
        return true;
    }
    return false;
}

bool Structure::removeSecondAtomOfDimerOn() {
    if (lattice.size() != (4 * str_size * str_size * str_size - 1)) {
        lattice.pop_back();
        return true;
    }
    return false;
}

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