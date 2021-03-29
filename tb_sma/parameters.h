//
// Created by General on 01.12.2020.
//

#pragma once
#include <vector>
#include <ostream>

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
    Parameters() = default;
    Parameters(const double r0,
               const double A0,
               const double A1,
               const double xi,
               const double p,
               const double q){
        p_[R0_LOC] = r0;
        p_[A0_LOC] = A0;
        p_[A1_LOC] = A1;
        p_[XI_LOC] = xi;
        p_[P_LOC] = p;
        p_[Q_LOC] = q;
    }

    double r0() const {return p_[R0_LOC];};
    double A0() const {return p_[A0_LOC];}
    double A1() const {return p_[A1_LOC];}
    double xi() const {return p_[XI_LOC];}
    double p() const {return p_[P_LOC];}
    double q() const {return p_[Q_LOC];}

    double& operator[] (int pos) {return p_[pos];}
    double operator[] (int pos) const { return p_[pos];}

    Parameters& operator*= (double alpha);
    Parameters& operator += (const Parameters& o);
    Parameters& operator /= (size_t N);
    Parameters operator * (double alpha);
private:
    double p_[PARAMETERS_SIZE] = {};
};

Parameters operator+ (const Parameters& lhs, const Parameters& rhs);
Parameters operator- (const Parameters& lhs, const Parameters& rhs);

std::ostream& operator << (std::ostream& os, const Parameters& p);

enum INTERACTION_ENUM {
    BB = 0,
    AA,
    AB
};

class InteractionParameters {
public:
    explicit InteractionParameters() = default;

    InteractionParameters(const Parameters& BB_params,
                          const Parameters& AA_params,
                          const Parameters& AB_params) {
        BB_AA_BA[0] = BB_params;
        BB_AA_BA[1] = AA_params;
        BB_AA_BA[2] = AB_params;
    }

    InteractionParameters(const Parameters& BB_params) {
        BB_AA_BA[0] = BB_params;
    }

    Parameters& operator[] (INTERACTION_ENUM inter_type) {return BB_AA_BA[inter_type];}
    Parameters operator[] (INTERACTION_ENUM inter_type) const { return BB_AA_BA[inter_type];}

    InteractionParameters& operator += (const InteractionParameters& add_params);
    InteractionParameters operator * (double alpha);
    InteractionParameters& operator /= (size_t N);
    InteractionParameters& operator *= (double alpha);
    InteractionParameters operator - (const InteractionParameters& add_params);
    InteractionParameters operator + (const InteractionParameters& add_params);
private:
    Parameters BB_AA_BA[3];
};

std::ostream& operator << (std::ostream& os, const InteractionParameters& ip);

struct ParametersEdges {
    double edges[18] = {1, 7,      // r0
                        -3, 3,    // A0
                        -5, 5,     // A1
                        0, 5,      // xi
                        3, 20,      // p
                        0, 10};     // q
    double operator [] (size_t ind) const;
};