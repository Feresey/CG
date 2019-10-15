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

Matrix Sh(float scale)
{
    return Matrix({
                      scale, 0, 0, 0,
                      0, scale, 0, 0,
                      0, 0, scale, 0,
                      0, 0, 0, 1 //
                  },
        4, 4);
}

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