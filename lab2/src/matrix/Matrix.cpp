#include "Matrix.hpp"

Matrix::Matrix(size_t N, size_t M)
    : N(N)
    , M(M)
    , _m(N * M)
{
    for (size_t i = 0; i < N; ++i)
        _m[i + M * i] = 1;
}

Matrix::Matrix(std::vector<float> m, size_t N, size_t M)
    : N(N)
    , M(M)
    , _m(m)
{
    if (m.size() != N * M)
        throw std::invalid_argument("Matrix size must be equal to " + std::to_string(N * M));
}

Matrix Matrix::operator*(const Matrix& second)
{
    if (second.N != this->M)
        throw std::invalid_argument("Number of matrix rows must be equal to " + std::to_string(this->M));
    Matrix tmp(this->M, second.N);
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            for (size_t k = 0; k < N; ++k)
                tmp[i + N * j] += (*this)[i + M * k] * second[k + M * j];
    return tmp;
}

QVector3D Matrix::operator*(const QVector3D& v)
{
    Matrix tmp = *this * Matrix({ v.x(), v.y(), v.z(), 1 }, 4, 1);
    return {
        tmp[0] / tmp[3],
        tmp[1] / tmp[3],
        tmp[2] / tmp[3]
    };
}

float Matrix::operator[](size_t i) const { return _m[i]; }
float& Matrix::operator[](size_t i) { return _m[i]; }