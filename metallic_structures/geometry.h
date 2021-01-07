//
// Created by General on 01.12.2020.
//

#pragma once
#include <iostream>

enum XYZ_ENUM {
    X_LOC = 0,
    Y_LOC,
    Z_LOC
};

struct Matrix;

class XYZ {
    double xyz_[3] = {0.0, 0.0, 0.0};
public:
    XYZ() = default;
    XYZ(double x, double y, double z) {
        xyz_[X_LOC] = x;
        xyz_[Y_LOC] = y;
        xyz_[Z_LOC] = z;
    }
    double operator[] (int i) const {return xyz_[i];};
    double& operator[] (int i) {return xyz_[i];};
    XYZ& operator-= (const XYZ& vec);
    XYZ& operator*= (double m);
    XYZ& operator*= (const Matrix& m);
    double dist(const XYZ& vec) const;
    double eu_norm() const;

};


XYZ operator- (const XYZ& lhs, const XYZ& rhs);
XYZ operator* (const XYZ& lhs, double rhs);
XYZ operator* (double lhs, const XYZ& rhs);



struct Matrix {
    double m[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix() = default;
    void setDiagonal(double(&diag)[3]);
    const double* operator[] (int row) const;
    double* operator[] (int row);
};

std::ostream& operator << (std::ostream& os, const Matrix& m);
XYZ operator* (const Matrix& lhs, const XYZ& rhs);



