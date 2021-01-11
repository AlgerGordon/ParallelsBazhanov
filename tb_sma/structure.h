//
// Created by General on 17.11.2020.
//


#pragma once
#include "atom.h"
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

    void createStructure(double lattice_const, int new_size, ATOM_ENUM a_type);

    void addAlloy(ATOM_ENUM a_type, size_t ind = 0);

    void removeAlloy(size_t ind);

    void addDimerIn(ATOM_ENUM a_type);

    void removeFirstAtomOfDimerIn();

    void removeSecondAtomOfDimerIn();

    void addDimerOn(ATOM_ENUM a_type);

    bool removeFirstAtomOfDimerOn();

    bool removeSecondAtomOfDimerOn();
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