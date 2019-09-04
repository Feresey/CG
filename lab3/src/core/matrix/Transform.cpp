// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <cmath>

#include "Matrix.hpp"
#include "Vector.hpp"

Matrix Rx(float alpha)
{
    return Matrix(
        {
            cosf(alpha), 0, -sinf(alpha), 0,
            0, 1, 0, 0,
            sinf(alpha), 0, cosf(alpha), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Ry(float beta)
{
    return Matrix(
        {
            1, 0, 0, 0,
            0, cosf(beta), sinf(beta), 0,
            0, -sinf(beta), cosf(beta), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Rz(float gamma)
{
    return Matrix(
        {
            cosf(gamma), -sinf(gamma), 0, 0,
            sinf(gamma), cosf(gamma), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Sh(float scale_x, float scale_y, float scale_z)
{
    return Matrix(
        {
            scale_x, 0, 0, 0,
            0, scale_y, 0, 0,
            0, 0, scale_z, 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Sh(float scale_all) { return Sh(scale_all, scale_all, scale_all); }

Matrix Move(const Vector3f& delta)
{
    return Matrix(
        {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            delta.x(), delta.y(), delta.z(), 1 //
        },
        4, 4);
}