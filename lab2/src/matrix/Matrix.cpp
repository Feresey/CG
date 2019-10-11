#include <QVector3D>
#include <QVector2D>

#include "Matrix.hpp"
#include "Polygon.hpp"


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
        throw std::invalid_argument("Matrix size must be equal to N*M : " + std::to_string(N * M));
}

Matrix Matrix::operator*(const Matrix& second) const
{
    return Matrix(*this) *= second;
}

Matrix& Matrix::operator*=(const Matrix& second)
{
    if (second.N != this->M)
        throw std::invalid_argument("Number of matrix rows must be equal to " + std::to_string(this->M));
    std::vector<float> tmp(this->N * second.M);
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < second.M; ++j)
            for (size_t k = 0; k < M; ++k)
                tmp[i + M * j] += (*this)[i + M * k] * second[k + second.M * j];

    _m = tmp;
    M = second.M;
    return *this;
}

QVector3D Matrix::operator*(const QVector3D& v) const
{
    Matrix tmp = *this * Matrix({ v.x(), v.y(), v.z(), 1 }, 4, 1);
    return QVector3D{
        tmp[0] / tmp[3],
        tmp[1] / tmp[3],
        tmp[2] / tmp[3]
    };
}

Polygon Matrix::operator*(const Polygon& v) const
{
    Polygon res(v);
    std::transform(v.cbegin(), v.cend(), res.begin(), [&](const QVector3D& p) { return *this * p; });
    return res;
}

QVector2D Matrix::projection(const QVector3D& point) const
{
    QVector3D tmp = *this * point;
    return QVector2D{ tmp.x(), tmp.y() };
}

float Matrix::operator[](size_t i) const { return _m[i]; }
float& Matrix::operator[](size_t i) { return _m[i]; }
