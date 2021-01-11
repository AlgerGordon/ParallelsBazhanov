//
// Created by General on 01.12.2020.
//

#include <parameters.h>

Parameters& Parameters::operator+= (const Parameters& o) {
    for (int i = 0; i < PARAMETERS_SIZE; ++i ) {
        p_[static_cast<PARAMETERS_ENUM>(i)] += o[i];
        // this->operator[](i) += o[i];
    }
    return *this;
}

Parameters& Parameters::operator/= (size_t N) {
    for (int i = 0; i < PARAMETERS_SIZE; ++i ) {
        p_[static_cast<PARAMETERS_ENUM>(i)] /= N;
        // this->operator[](i) += o[i];
    }
    return *this;
}

Parameters& Parameters::operator*= (double alpha) {
    for (int i = 0; i < PARAMETERS_SIZE; ++i ) {
        p_[static_cast<PARAMETERS_ENUM>(i)] *= alpha;
        // this->operator[](i) += o[i];
    }
    return *this;
}

Parameters Parameters::operator* (double alpha) {
    Parameters res;
    for (int i = 0; i < PARAMETERS_SIZE; ++i ) {
        res[static_cast<PARAMETERS_ENUM>(i)] = p_[static_cast<PARAMETERS_ENUM>(i)] * alpha;
        // this->operator[](i) += o[i];
    }
    return res;
}

Parameters operator+ (const Parameters& lhs, const Parameters& rhs) {
    return Parameters(
                lhs[R0_LOC] + rhs[R0_LOC],
                lhs[A0_LOC] + rhs[A0_LOC],
                lhs[A1_LOC] + rhs[A1_LOC],
                lhs[XI_LOC] + rhs[XI_LOC],
                lhs[P_LOC] + rhs[P_LOC],
                lhs[Q_LOC] + rhs[Q_LOC]
            );
}

Parameters operator- (const Parameters& lhs, const Parameters& rhs) {
    return Parameters(
            lhs[R0_LOC] - rhs[R0_LOC],
            lhs[A0_LOC] - rhs[A0_LOC],
            lhs[A1_LOC] - rhs[A1_LOC],
            lhs[XI_LOC] - rhs[XI_LOC],
            lhs[P_LOC] - rhs[P_LOC],
            lhs[Q_LOC] - rhs[Q_LOC]
        );
}

double ParametersEdges::operator [] (size_t ind) const {
    return edges[ind];
}

InteractionParameters& InteractionParameters::operator += (const InteractionParameters& add_params) {
    for (INTERACTION_ENUM it : {BB, AA, AB}) {
        BB_AA_BA[it] += add_params[it];
    }
    return *this;
}

InteractionParameters& InteractionParameters::operator /= (size_t N) {
    for (INTERACTION_ENUM it : {BB, AA, AB}) {
        BB_AA_BA[it] /= N;
    }
    return *this;
}

InteractionParameters InteractionParameters::operator * (double alpha) {
    InteractionParameters res;
    for (INTERACTION_ENUM it : {BB, AA, AB}) {
        res[it] = BB_AA_BA[it] * alpha;
    }
    return res;
}

InteractionParameters InteractionParameters::operator - (const InteractionParameters& add_params) {
    InteractionParameters res;
    for (INTERACTION_ENUM it : {BB, AA, AB}) {
        res[it] = BB_AA_BA[it] - add_params[it];
    }
    return res;
}

InteractionParameters InteractionParameters::operator + (const InteractionParameters& add_params) {
    InteractionParameters res;
    for (INTERACTION_ENUM it : {BB, AA, AB}) {
        res[it] = BB_AA_BA[it] + add_params[it];
    }
    return res;
}

InteractionParameters& InteractionParameters::operator *= (double alpha) {
    for (INTERACTION_ENUM it : {BB, AA, AB}) {
        BB_AA_BA[it] *= alpha;
    }
    return *this;
}

std::ostream& operator << (std::ostream& os, const Parameters& p) {
    os << "\tr0: " << p[R0_LOC] << '\n';
    os << "\tA0: " << p[A0_LOC] << '\n';
    os << "\tA1: " << p[A1_LOC] << '\n';
    os << "\txi: " << p[XI_LOC] << '\n';
    os << "\tp: " << p[P_LOC] << '\n';
    os << "\tq: " << p[Q_LOC] << '\n';
    return os;
}

std::ostream& operator << (std::ostream& os, const InteractionParameters& ip) {
    for (INTERACTION_ENUM inter_type : {BB, AA, AB}) {
        switch (inter_type) {
            case BB:
                os << "BB: " << '\n';
                break;
            case AA:
                os << "AA: " << '\n';
                break;
            case AB:
                os << "AB: " << '\n';
                break;
            default:
                os << "Unknown interaction:" << '\n';
                break;
        }
        os << ip[inter_type];
    }
    return os;
}
