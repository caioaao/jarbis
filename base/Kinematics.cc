#include "Kinematics.h"

#include <cmath>

namespace base {
    Matrix<float, 3, 3>
    rotation_matrix(Matrix<float, 2, 1> reference, float angle) {
        Matrix<float, 3, 3> mat;

        mat = rotation_matrix(angle);

        for(unsigned i = 0; i < 2; ++i) {
            mat[i][2] = reference[i][0] - (reference[0][0] * mat[i][0] +
                                           reference[1][0] * mat[i][1]);
        }

        return mat;
    }


    Matrix<float, 3, 3>
    rotation_matrix(float angle) {
        Matrix<float, 3, 3> mat;

        mat[0] = {(float)cos(angle), -(float)sin(angle), 0};
        mat[1] = {       -mat[0][1],          mat[0][0], 0};
        mat[2] = {                0,                  0, 1};

        return mat;
    }


    Matrix<float, 3, 3>
    translation_matrix(float delta_x, float delta_y) {
        Matrix<float, 3, 3> mat = identity_matrix<float, 3>();

        mat[0][2] = delta_x;
        mat[1][2] = delta_y;

        return mat;
    }

    float
    deg_to_rad(float deg) {
        return deg * PI / 180;
    }
}
