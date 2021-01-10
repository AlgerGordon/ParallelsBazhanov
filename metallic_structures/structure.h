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
    int str_size;
    Lattice lattice;
    ATOM_ENUM base_type;
    double lattice_constant;

    void createStructure(double lattice_const, int new_size, ATOM_ENUM a_type) {
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

    void addAlloy(ATOM_ENUM a_type, size_t ind = 0) {
        lattice[ind].set_type(a_type);
    }

    void removeAlloy(size_t ind) {
        lattice[ind].set_type(base_type);
    }

    void addDimerIn(ATOM_ENUM a_type) {
        size_t kAtomInd1 = (str_size - 1) * 4 + 2;
        size_t kAtomInd2 = (str_size - 1) * 4 + 3;
        lattice[kAtomInd1].set_type(a_type);
        lattice[kAtomInd2].set_type(a_type);
    }

    void removeFirstAtomOfDimerIn() {
        size_t kAtomInd1 = (str_size - 1) * 4 + 2;
        lattice[kAtomInd1].set_type(base_type);
    }

    void removeSecondAtomOfDimerIn() {
        size_t kAtomInd2 = (str_size - 1) * 4 + 3;
        lattice[kAtomInd2].set_type(base_type);
    }

    void addDimerOn(ATOM_ENUM a_type) {
        XYZ tmp_pos = {0, 0, 1.0 * str_size};
        XYZ pos1 = lattice[0].pos() + tmp_pos;
        XYZ pos2 = lattice[1].pos() + tmp_pos;
        lattice.push_back(Atom(a_type, pos1));
        lattice.push_back(Atom(a_type, pos2));
    }

    bool removeFirstAtomOfDimerOn() {
        if (lattice.size() != 4 * str_size * str_size * str_size) {
            lattice.pop_back();
            return true;
        }
        return false;
    }

    bool removeSecondAtomOfDimerOn() {
        if (lattice.size() != (4 * str_size * str_size * str_size - 1)) {
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
                                         //const XYZ& period,
                                         double lattice_const,
                                         double str_size,
                        const Matrix& deformation,
                        DEF_MATRICES_ENUM defType = NO_DEF)  {
    XYZ vec;
    vec = tmp_atom.pos() - pivot_atom.pos();

    if (zPeriodic == ZPERIOD::Z_ON) {
        tmp_atom.pos(Z_LOC) += ((std::abs(vec[Z_LOC]) < (1.0 * str_size/ 2))
                                ? 0
                                : -1.0 * str_size * sgn(vec[Z_LOC]));
    }

    for (XYZ_ENUM coord : {X_LOC, Y_LOC}) {
        tmp_atom.pos(coord) += ((std::abs(vec[coord]) < (1.0 * str_size / 2))
                                ? 0
                                : -1.0 * str_size * sgn(vec[coord]));
    }

    pivot_atom.pos() *= lattice_const;
    tmp_atom.pos() *= lattice_const;

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