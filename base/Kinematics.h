#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "base/LinAlg.h"

#define PI 3.14159265

namespace base {
    Matrix<float, 3, 3> rotation_matrix(float angle);
    Matrix<float, 3, 3> rotation_matrix(Matrix<float, 2, 1> reference,
                                        float angle);
    Matrix<float, 3, 3> translation_matrix(float delta_x, float delta_y);

    float deg_to_rad(float deg);
}

#endif
