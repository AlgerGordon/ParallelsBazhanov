//
// Created by General on 01.12.2020.
//

#pragma once
#include <iostream>

enum M_QUANTITIES_ENUM {
    E_COH_LOC,
    B_LOC,
    C11_LOC,
    C12_LOC,
    C44_LOC,
    M_QUANTITIES_SIZE
};

enum class MATERIAL_ENUM {
    AU,
    CO,
    CU,
    AG
};

enum class ALLOY_ENUM {
    AU_CO
};

class MaterialQuantities {
public:
    explicit MaterialQuantities(MATERIAL_ENUM type) : type_(type) {}
    MaterialQuantities(double E_coh,
                       double B,
                       double C11,
                       double C12,
                       double C44,
                       MATERIAL_ENUM type) : type_(type) {
        q_[E_COH_LOC] = E_coh;
        q_[B_LOC] = B;
        q_[C11_LOC] = C11;
        q_[C12_LOC] = C12;
        q_[C44_LOC] = C44;
    }

    double& operator[] (M_QUANTITIES_ENUM pos) {return q_[pos];}
    const double& operator[] (M_QUANTITIES_ENUM pos) const { return q_[pos];}
    MATERIAL_ENUM type() { return type_; }

private:
    double q_[M_QUANTITIES_SIZE] = {};
    MATERIAL_ENUM type_;
};

std::ostream& operator << (std::ostream& os, MaterialQuantities mq);

class AlloysQuantities {
public:

};

// Test

