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
   explicit Atom(ATOM_ENUM type, double x = 0, double y = 0, double z = 0) : pos_(x,y,z) {
        type_ = type;
    }
    Atom(ATOM_ENUM type, XYZ pos) : pos_(pos) {
        type_ = type;
    }
    XYZ pos() const {return pos_;}
    double& pos(size_t coord) {return pos_[coord];}
    ATOM_ENUM type() const { return type_; }
    void set_type(ATOM_ENUM a_type) { type_ = a_type;}
    void operator*= (const Matrix& m) {
        pos_ *= m;
    }
};
