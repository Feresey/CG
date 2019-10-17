#include <cmath>

#include "Matrix.hpp"

Matrix Rx(float phi)
{
    return Matrix(
        {
            cosf(phi), 0, -sinf(phi), 0,
            0, 1, 0, 0,
            sinf(phi), 0, cosf(phi), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Ry(float theta)
{
    return Matrix(
        {
            1, 0, 0, 0,
            0, cosf(theta), sinf(theta), 0,
            0, -sinf(theta), cosf(theta), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Sh(float scale_x, float scale_y, float scale_z)
{
    return Matrix({
                      scale_x, 0, 0, 0,
                      0, scale_y, 0, 0,
                      0, 0, scale_z, 0,
                      0, 0, 0, 1 //
                  },
        4, 4);
}

Matrix Sh(float scale_all) { return Sh(scale_all, scale_all, scale_all); }

Matrix Move(const QVector3D& delta)

{
    return Matrix({
                      1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      delta.x(), delta.y(), delta.z(), 1 //
                  },
        4, 4);
}