//
// Created by General on 17.11.2020.
//


#pragma once
#include "atom.h"
#include "quantities.h"
#include <vector>
#include <cmath>

enum class ZPERIOD {
    Z_ON,
    Z_OFF
};

enum DEF_MATRICES_ENUM {
    NO_DEF = 0,
    B_DEF,
    C11_DEF,
    C12_DEF,
    C44_DEF,
    DEF_MATR_SIZE
};

using Lattice = std::vector<Atom>;

struct Structure {
    int size;
    XYZ period;
    Lattice lattice;
    ATOM_ENUM base_type;

    void createStructure(double lattice_constant, int new_size, ATOM_ENUM a_type) {
        this->lattice = {};
        this->size = new_size;
        this->period = {size * lattice_constant, size * lattice_constant, size * lattice_constant};
        this->base_type = a_type;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    this->lattice.emplace_back(Atom(a_type, (0 + i) * lattice_constant, (0 + j) * lattice_constant,
                                                    (0 + k) * lattice_constant));
                    this->lattice.emplace_back(Atom(a_type, (0.5 + i) * lattice_constant, (0.5 + j) * lattice_constant,
                                                    (0 + k) * lattice_constant));
                    this->lattice.emplace_back(Atom(a_type, (0 + i) * lattice_constant, (0.5 + j) * lattice_constant,
                                                    (0.5 + k) * lattice_constant));
                    this->lattice.emplace_back(Atom(a_type, (0.5 + i) * lattice_constant, (0 + j) * lattice_constant,
                                                    (0.5 + k) * lattice_constant));
                }
            }
        }
    }

    void addAlloy(ATOM_ENUM a_type, size_t ind = 0) {
        lattice[ind].set_type(a_type);
    }

    void removeAlloy(size_t ind) {
        lattice[ind].set_type(base_type);
    }

    void addDimerIn(ATOM_ENUM a_type) {
        size_t kAtomInd1 = (size - 1) * 4 + 2;
        size_t kAtomInd2 = (size - 1) * 4 + 3;
        lattice[kAtomInd1].set_type(a_type);
        lattice[kAtomInd2].set_type(a_type);
    }

    void removeFirstAtomOfDimerIn() {
        size_t kAtomInd1 = (size - 1) * 4 + 2;
        lattice[kAtomInd1].set_type(base_type);
    }

    void removeSecondAtomOfDimerIn() {
        size_t kAtomInd2 = (size - 1) * 4 + 3;
        lattice[kAtomInd2].set_type(base_type);
    }

    void addDimerOn(ATOM_ENUM a_type) {
        XYZ tmp_pos = {0, 0, period[Z_LOC]};
        XYZ pos1 = lattice[0].pos() + tmp_pos;
        XYZ pos2 = lattice[1].pos() + tmp_pos;
        lattice.push_back(Atom(a_type, pos1));
        lattice.push_back(Atom(a_type, pos2));
    }

    bool removeFirstAtomOfDimerOn() {
        if (lattice.size() != 4 * this->size * this->size * this->size) {
            lattice.pop_back();
            return true;
        }
        return false;
    }

    bool removeSecondAtomOfDimerOn() {
        if (lattice.size() != (4 * this->size * this->size * this->size - 1)) {
            lattice.pop_back();
            return true;
        }
        return false;
    }
};

void operator *= (Lattice& l, const Matrix& m);

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template<ZPERIOD zPeriodic>
double minimizeDistance(Atom pivot_atom, Atom tmp_atom,
                                         const XYZ& period,
                        const Matrix& deformation, ATOM_ENUM structure_type,
                        DEF_MATRICES_ENUM defType = NO_DEF)  {
    XYZ vec;
    vec = tmp_atom.pos() - pivot_atom.pos();

    if (zPeriodic == ZPERIOD::Z_ON) {
        tmp_atom.pos(Z_LOC) += ((std::abs(vec[Z_LOC]) < (period[Z_LOC] / 2))
                                ? 0
                                : -period[Z_LOC] * sgn(vec[Z_LOC]));
    }

    for (XYZ_ENUM coord : {X_LOC, Y_LOC}) {
        tmp_atom.pos(coord) += ((std::abs(vec[coord]) < (period[coord] / 2))
                                ? 0
                                : -period[coord] * sgn(vec[coord]));
    }

    if (defType != NO_DEF) {
        pivot_atom *= deformation;
        tmp_atom *= deformation;
    }

    vec = tmp_atom.pos() - pivot_atom.pos();

    return vec.eu_norm();
}

struct DefMatrices {
    std::vector<Matrix> to_vec_;
    explicit DefMatrices(double delta);
};


// Tests

void TestStructure();
void TestMinimizeDist();