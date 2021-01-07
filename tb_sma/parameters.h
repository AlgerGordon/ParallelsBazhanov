//
// Created by General on 01.12.2020.
//

#pragma once

enum PARAMETERS_ENUM {
    R0_LOC = 0,
    A0_LOC,
    A1_LOC,
    XI_LOC,
    P_LOC,
    Q_LOC,
    PARAMETERS_SIZE
};


class Parameters {
public:
    Parameters(const double r0,
               const double A0,
               const double A1,
               const double xi,
               const double p,
               const double q){
        //  lattice_constant
        p_[R0_LOC] = r0;
        p_[A0_LOC] = A0;
        p_[A1_LOC] = A1;
        p_[XI_LOC] = xi;
        p_[P_LOC] = p;
        p_[Q_LOC] = q;
    }

    const double& r0() const {return p_[R0_LOC];};
    const double& A0() const {return p_[A0_LOC];}
    const double& A1() const {return p_[A1_LOC];}
    const double& xi() const {return p_[XI_LOC];}
    const double& p() const {return p_[P_LOC];}
    const double& q() const {return p_[Q_LOC];}

    double& operator[] (int pos) {return p_[pos];}
    double operator[] (int pos) const { return p_[pos];}

    Parameters& operator+= (const Parameters& o);
private:
    double p_[PARAMETERS_SIZE];
};

Parameters operator+ (const Parameters& lhs, const Parameters& rhs);

