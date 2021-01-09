//
// Created by General on 08.12.2020.
//


#include <quantities.h>

std::ostream& operator << (std::ostream& os, Quantities q) {
    switch (q.base_type())
    {
        case ATOM_ENUM::AU:
            os << "AU:" << std::endl;
            break;
        case ATOM_ENUM::CO:
            os << "CO:" << std::endl;
            break;
        case ATOM_ENUM::CU:
            os << "CU:" << std::endl;
            break;
        case ATOM_ENUM::AG:
            os << "AG:" << std::endl;
            break;
        default:
            os << "Unknown material:" << std::endl;
            break;
    }

    os << "E_coh: " << q[E_COH_LOC] << std::endl;
    os << "B: " << q[B_LOC] << std::endl;
    os << "C11: " << q[C11_LOC] << std::endl;
    os << "C12: " << q[C12_LOC] << std::endl;
    os << "C44: " << q[C44_LOC] << std::endl;

    switch (q.alloy_type())
    {
        case ATOM_ENUM::AU:
            os << "AU" << std::endl;
            break;
        case ATOM_ENUM::CO:
            os << "CO" << std::endl;
            break;
        case ATOM_ENUM::CU:
            os << "CU" << std::endl;
            break;
        case ATOM_ENUM::AG:
            os << "AG" << std::endl;
            break;
        default:
            os << "Unknown material:" << std::endl;
            break;
    }

    switch (q.base_type())
    {
        case ATOM_ENUM::AU:
            os << "-AU:" << std::endl;
            break;
        case ATOM_ENUM::CO:
            os << "-CO:" << std::endl;
            break;
        case ATOM_ENUM::CU:
            os << "-CU:" << std::endl;
            break;
        case ATOM_ENUM::AG:
            os << "-AG:" << std::endl;
            break;
        default:
            os << "-Unknown material:" << std::endl;
            break;
    }

    os << "E_sol: " << q[E_SOL_LOC] << std::endl;
    os << "E_dim_in: " << q[E_DIM_IN_LOC] << std::endl;
    os << "E_dim_on: " << q[E_DIM_ON_LOC] << std::endl;

    return os;
}

std::ostream& operator << (std::ostream& os, MaterialQuantities q) {
    switch (q.base_type())
    {
        case ATOM_ENUM::AU:
            os << "AU:" << std::endl;
            break;
        case ATOM_ENUM::CO:
            os << "CO:" << std::endl;
            break;
        case ATOM_ENUM::CU:
            os << "CU:" << std::endl;
            break;
        case ATOM_ENUM::AG:
            os << "AG:" << std::endl;
            break;
        default:
            os << "Unknown material:" << std::endl;
            break;
    }

    os << "E_coh: " << q[M_E_COH_LOC] << std::endl;
    os << "B: " << q[M_B_LOC] << std::endl;
    os << "C11: " << q[M_C11_LOC] << std::endl;
    os << "C12: " << q[M_C12_LOC] << std::endl;
    os << "C44: " << q[M_C44_LOC] << std::endl;

    return os;
}

std::ostream& operator << (std::ostream& os, AlloyQuantities q){
    switch (q.alloy_type())
    {
        case ATOM_ENUM::AU:
            os << "AU" << std::endl;
            break;
        case ATOM_ENUM::CO:
            os << "CO" << std::endl;
            break;
        case ATOM_ENUM::CU:
            os << "CU" << std::endl;
            break;
        case ATOM_ENUM::AG:
            os << "AG" << std::endl;
            break;
        default:
            os << "Unknown material:" << std::endl;
            break;
    }

    switch (q.base_type())
    {
        case ATOM_ENUM::AU:
            os << "-AU:" << std::endl;
            break;
        case ATOM_ENUM::CO:
            os << "-CO:" << std::endl;
            break;
        case ATOM_ENUM::CU:
            os << "-CU:" << std::endl;
            break;
        case ATOM_ENUM::AG:
            os << "-AG:" << std::endl;
            break;
        default:
            os << "-Unknown material:" << std::endl;
            break;
    }

    os << "E_sol: " << q[A_E_SOL_LOC] << std::endl;
    os << "E_dim_in: " << q[A_E_DIM_IN_LOC] << std::endl;
    os << "E_dim_on: " << q[A_E_DIM_ON_LOC] << std::endl;

    return os;
}
