//
// Created by General on 01.12.2020.
//

#pragma once
#include <iostream>
#include "structure.h"

enum QUANTITIES_ENUM {
    E_COH_LOC,
    B_LOC,
    C11_LOC,
    C12_LOC,
    C44_LOC,
    E_SOL_LOC,
    E_DIM_IN_LOC,
    E_DIM_ON_LOC,
    QUANTITIES_SIZE
};

class Quantities {
public:
    explicit Quantities(ATOM_ENUM type) : base_type_(type) {}
    Quantities(double E_coh,
               double B,
               double C11,
               double C12,
               double C44,
               double E_sol,
               double E_dim_in,
               double E_dim_on,
               ATOM_ENUM base_type,
               ATOM_ENUM alloy_type) : base_type_(base_type)
                                        , alloy_type_(alloy_type)  {
        q_[E_COH_LOC] = E_coh;
        q_[B_LOC] = B;
        q_[C11_LOC] = C11;
        q_[C12_LOC] = C12;
        q_[C44_LOC] = C44;
        q_[E_SOL_LOC] = E_sol;
        q_[E_DIM_IN_LOC] = E_dim_in;
        q_[E_DIM_ON_LOC] = E_dim_on;
    }

    double& operator[] (QUANTITIES_ENUM pos) {return q_[pos];}
    const double& operator[] (QUANTITIES_ENUM pos) const { return q_[pos];}
    ATOM_ENUM base_type() { return base_type_; }
    ATOM_ENUM alloy_type() { return alloy_type_; }
private:
    double q_[QUANTITIES_SIZE] = {};
    ATOM_ENUM base_type_;
    ATOM_ENUM alloy_type_;
};

std::ostream& operator << (std::ostream& os, Quantities q);

////////////////////////////////////////////////////////////////////////////////

enum M_QUANTITIES_ENUM {
    M_E_COH_LOC,
    M_B_LOC,
    M_C11_LOC,
    M_C12_LOC,
    M_C44_LOC,
    M_QUANTITIES_SIZE
};

class MaterialQuantities {
public:
    explicit MaterialQuantities(ATOM_ENUM type) : base_type_(type) {}
    MaterialQuantities(double E_coh,
               double B,
               double C11,
               double C12,
               double C44,
               ATOM_ENUM type) : base_type_(type) {
        q_[M_E_COH_LOC] = E_coh;
        q_[M_B_LOC] = B;
        q_[M_C11_LOC] = C11;
        q_[M_C12_LOC] = C12;
        q_[M_C44_LOC] = C44;
    }

    double& operator[] (M_QUANTITIES_ENUM pos) {return q_[pos];}
    const double& operator[] (M_QUANTITIES_ENUM pos) const { return q_[pos];}
    ATOM_ENUM base_type() { return base_type_; }
private:
    double q_[M_QUANTITIES_SIZE] = {};
    ATOM_ENUM base_type_;
};

std::ostream& operator << (std::ostream& os, MaterialQuantities q);

///////////////////////////////////////////////////////////////////////////////

enum A_QUANTITIES_ENUM {
    A_E_SOL_LOC,
    A_E_DIM_IN_LOC,
    A_E_DIM_ON_LOC,
    A_QUANTITIES_SIZE
};

class AlloyQuantities {
public:
    explicit AlloyQuantities(ATOM_ENUM type) : alloy_type_(type) {}
    AlloyQuantities(double E_sol,
                       double E_dim_in,
                       double E_dim_on,
                       ATOM_ENUM base_type,
                       ATOM_ENUM alloy_type) : base_type_(base_type), alloy_type_(alloy_type) {
        q_[A_E_SOL_LOC] = E_sol;
        q_[A_E_DIM_IN_LOC] = E_dim_in;
        q_[A_E_DIM_ON_LOC] = E_dim_on;
    }

    double& operator[] (A_QUANTITIES_ENUM pos) {return q_[pos];}
    const double& operator[] (A_QUANTITIES_ENUM pos) const { return q_[pos];}
    ATOM_ENUM alloy_type() { return alloy_type_; }
    ATOM_ENUM base_type() { return base_type_; }
private:
    double q_[A_QUANTITIES_SIZE] = {};
    ATOM_ENUM alloy_type_;
    ATOM_ENUM base_type_;
};

std::ostream& operator << (std::ostream& os, AlloyQuantities q);

// Test
void TestMaterialQuantities();
void TestAlloyQuantities();
