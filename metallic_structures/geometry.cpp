//
// Created by General on 01.12.2020.
//

#include <geometry.h>
#include <cmath>

XYZ& XYZ::operator-= (const XYZ& vec){
    this->xyz_[X_LOC] -= vec[X_LOC];
    this->xyz_[Y_LOC] -= vec[Y_LOC];
    this->xyz_[Z_LOC] -= vec[Z_LOC];
    return *this;
}

XYZ& XYZ::operator*= (double multiplier){
    this->xyz_[X_LOC] *= multiplier;
    this->xyz_[Y_LOC] *= multiplier;
    this->xyz_[Z_LOC] *= multiplier;
    return *this;
}

XYZ& XYZ::operator*= (const Matrix& m) {
    double tmp_x = m[X_LOC][X_LOC] * xyz_[X_LOC] + m[X_LOC][Y_LOC] * xyz_[Y_LOC];
    double tmp_y = m[Y_LOC][X_LOC] * xyz_[X_LOC] + m[Y_LOC][Y_LOC] * xyz_[Y_LOC];
    xyz_[X_LOC] = tmp_x;
    xyz_[Y_LOC] = tmp_y;
    xyz_[Z_LOC] *= m[Z_LOC][Z_LOC];
    return *this;
}

XYZ operator- (const XYZ& lhs, const XYZ& rhs) {
    return XYZ(lhs[X_LOC] - rhs[X_LOC],
               lhs[Y_LOC] - rhs[Y_LOC],
               lhs[Z_LOC] - rhs[Z_LOC]);
}

XYZ operator* (const XYZ& lhs, double rhs){
    return XYZ(lhs[X_LOC] * rhs, lhs[Y_LOC] * rhs, lhs[Z_LOC] * rhs);
}

XYZ operator* (double lhs, const XYZ& rhs){
    return XYZ(lhs * rhs[X_LOC], lhs * rhs[Y_LOC], lhs * rhs[Z_LOC]);
}

// Matrix

const double* Matrix::operator[] (int row) const {
    return m[row];
}

double* Matrix::operator[] (int row) {
    return m[row];
}

XYZ operator* (const Matrix& lhs, const XYZ& rhs) {
    XYZ vec;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            vec[i] += lhs[i][j] * rhs[j];
        }
    }
    return vec;
}


void Matrix::setDiagonal(double(&diag)[3]) {
    for (int i = 0; i < 3; ++i) {
        m[i][i] = diag[i];
    }
}

std::ostream& operator << (std::ostream& os, const Matrix& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            os.width(10);
            os << m[i][j] << " ";
        }
        os << std::endl;
    }

    return os;
}