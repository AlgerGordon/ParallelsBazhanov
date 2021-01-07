//
// Created by General on 01.12.2020.
//

#pragma once
#include "geometry.h"

enum class ATOM_ENUM {
    AU,
    CO,
    CU,
    AG
};

class Atom {
    XYZ pos_;
    ATOM_ENUM type_;
public:
    Atom(ATOM_ENUM type, double x = 0, double y = 0, double z = 0) : pos_(x,y,z) {
        type_ = type;
    }
    XYZ pos() const {return pos_;}
    ATOM_ENUM type() const { return type_; }
    void operator*= (const Matrix& m) {
        pos_ *= m;
    }
};
