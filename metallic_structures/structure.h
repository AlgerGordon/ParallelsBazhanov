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
};

template<ATOM_ENUM a_type>
void createStructure(Structure& s, double lattice_constant, int size) {
    s.lattice = {};
    s.size = size;
    s.period = {size * lattice_constant, size * lattice_constant, size * lattice_constant};

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                s.lattice.emplace_back(Atom(a_type, (0 + i) * lattice_constant, (0 + j) * lattice_constant,
                                            (0 + k) * lattice_constant));
                s.lattice.emplace_back(Atom(a_type, (0 + i) * lattice_constant, (0.5 + j) * lattice_constant,
                                            (0.5 + k) * lattice_constant));
                s.lattice.emplace_back(Atom(a_type, (0.5 + i) * lattice_constant, (0.5 + j) * lattice_constant,
                                            (0 + k) * lattice_constant));
                s.lattice.emplace_back(Atom(a_type, (0.5 + i) * lattice_constant, (0 + j) * lattice_constant,
                                            (0.5 + k) * lattice_constant));
            }
        }
    }


}

void operator *= (Lattice& l, const Matrix& m);

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template<ZPERIOD zPeriodic>
double minimizeDistance(XYZ pivot, XYZ tmp, const XYZ& period,
                            const Matrix& deformation,
                            DEF_MATRICES_ENUM defType = NO_DEF)  {

    XYZ vec = tmp - pivot;
    if (zPeriodic == ZPERIOD::Z_ON) {
        tmp[Z_LOC] += ((std::abs(vec[Z_LOC]) < (period[Z_LOC]/2))
                       ? 0
                       : -period[Z_LOC] * sgn(vec[Z_LOC]));
    }
    for (XYZ_ENUM pos : {X_LOC, Y_LOC}) {
        tmp[pos] += ((std::abs(vec[pos]) < (period[pos]/2))
                     ? 0
                     : -period[pos] * sgn(vec[pos]));
    }

    if (defType != NO_DEF) {
        pivot *= deformation;
        tmp *= deformation;
    }

    vec = tmp - pivot;

    return sqrt(vec[X_LOC] * vec[X_LOC] + vec[Y_LOC] * vec[Y_LOC] + vec[Z_LOC] * vec[Z_LOC]);

}

struct DefMatrices {
    std::vector<Matrix> to_vec_;
    explicit DefMatrices(double delta);
};


// Tests

void TestStructure();
void TestMinimizeDist();