//
// Created by General on 08.12.2020.
//


#include <quantities.h>

std::ostream& operator << (std::ostream& os, MaterialQuantities mq) {
    switch (mq.type())
    {
        case MATERIAL_ENUM::AU:
            os << "AU:" << std::endl;
            break;
        case MATERIAL_ENUM::CO:
            os << "CO:" << std::endl;
            break;
        case MATERIAL_ENUM::CU:
            os << "CU:" << std::endl;
            break;
        case MATERIAL_ENUM::AG:
            os << "AG:" << std::endl;
            break;
        default:
            os << "Unknown material:" << std::endl;
            break;
    }
    os << "E_coh: " << mq[E_COH_LOC] << std::endl;
    os << "B: " << mq[B_LOC] << std::endl;
    os << "C11: " << mq[C11_LOC] << std::endl;
    os << "C12: " << mq[C12_LOC] << std::endl;
    os << "C44: " << mq[C44_LOC] << std::endl;
    return os;
}
