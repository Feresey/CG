#include "Matrix.hpp"
#include "Polygon.hpp"

Matrix::Matrix(size_t N, size_t M)
    : rows(N)
    , colomns(M)
    , _m(rows * colomns)
{
    for (size_t i = 0; i < N; ++i)
        (*this)(i, i) = 1;
}

Matrix::Matrix(std::vector<float> m, size_t N, size_t M)
    : rows(N)
    , colomns(M)
    , _m(m)
{
    if (m.size() != rows * colomns)
        throw std::invalid_argument("Matrix size must be equal to N*M : " + std::to_string(rows * colomns));
}

Matrix Matrix::operator*(const Matrix& second) const { return Matrix(*this) *= second; }

Matrix& Matrix::operator*=(const Matrix& second)
{
    if (second.rows != this->colomns)
        throw std::invalid_argument("Number of matrix rows must be equal to " + std::to_string(this->colomns));
    std::vector<float> tmp(this->rows * second.colomns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < second.colomns; ++j)
            for (size_t k = 0; k < colomns; ++k)
                tmp[i + colomns * j] += (*this)(i, k) * second(k, j);

    _m = tmp;
    colomns = second.colomns;
    return *this;
}

QVector3D Matrix::operator*(const QVector3D& v) const
{
    Matrix tmp = *this * Matrix{{ v.x(), v.y(), v.z(), 1 }, 4, 1};
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

float Matrix::operator[](size_t i) const { return _m[i]; }
float& Matrix::operator[](size_t i) { return _m[i]; }

float& Matrix::operator()(size_t i, size_t j) { return _m[i * colomns * j]; }
float Matrix::operator()(size_t i, size_t j) const { return _m[i * colomns * j]; }
