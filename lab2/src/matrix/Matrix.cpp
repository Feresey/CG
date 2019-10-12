#include "Matrix.hpp"
#include "Polygon.hpp"

Matrix::Matrix(size_t N, size_t M)
    : rows(N)
    , colomns(M)
    , _m(rows * colomns, 0.0f)
{
    // size_t mx = std::min(rows, colomns);

    // for (size_t i = 0; i < mx; ++i)
    //     _m[i + rows * i] = 1;
}

Matrix::Matrix(const std::vector<float>& m, size_t N, size_t M)
    : rows(N)
    , colomns(M)
    , _m(m)
{
    if (m.size() != rows * colomns)
        throw std::invalid_argument("Matrix size must be equal to N*M : " + std::to_string(rows * colomns));
}

#include <iostream>

std::ostream& operator<<(std::ostream& os, const QVector3D src)
{
    os << "(" << src[0] << ',' << src[1] << ',' << src[2] << ')';
    return os;
}

Matrix::Matrix(const std::vector<Polygon>& src, const QVector3D& inside)
    : Matrix(4, src.size())
{
    for (size_t i = 0; i < src.size(); ++i) {
        std::vector<float> tmp = src[i].to_plane();
        _m[colomns * 0 + i] = tmp[0] / abs(tmp[3]);
        _m[colomns * 1 + i] = tmp[1] / abs(tmp[3]);
        _m[colomns * 2 + i] = tmp[2] / abs(tmp[3]);
        _m[colomns * 3 + i] = tmp[3] / abs(tmp[3]);
    }
    std::cout.precision(5);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < colomns; ++j)
            std::cout << _m[i * colomns + j] << "\t\t";
        std::cout << '\n';
    }

    Matrix tmp = Matrix{ { inside.x(), inside.y(), inside.z(), 1 }, 1, 4 } * (*this);
    std::cout << "inside: " << inside << std::endl;
    for (size_t j = 0; j < src.size(); ++j)
        std::cout << tmp[j] << "\t\t";
    std::cout << "\n\n";
    for (size_t i = 0; i < src.size(); ++i) {
        if (tmp[i] > 0.0f) {
            _m[colomns * 0 + i] *= -1;
            _m[colomns * 1 + i] *= -1;
            _m[colomns * 2 + i] *= -1;
            _m[colomns * 3 + i] *= -1;
        }
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < colomns; ++j)
            std::cout << _m[i * colomns + j] << "\t";
        std::cout << '\n';
    }
    std::cout << std::endl;
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
                tmp[i * colomns + j] += _m[i * colomns + k] * second(k, j);

    _m = tmp;
    colomns = second.colomns;
    return *this;
}

QVector3D Matrix::operator*(const QVector3D& v) const
{
    Matrix tmp = Matrix{ { v.x(), v.y(), v.z(), 1 }, 1, 4 } * (*this);
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

float& Matrix::operator()(size_t i, size_t j)
{
    if (i >= rows || j >= colomns)
        throw std::invalid_argument("wrong element position: ("
            + std::to_string(i) + "," + std::to_string(j)
            + "), expected :(" + std::to_string(rows) + "," + std::to_string(colomns) + ")");
    return _m[i * colomns + j];
}

float Matrix::operator()(size_t i, size_t j) const
{
    if (i >= rows || j >= colomns)
        throw std::invalid_argument("wrong element position: ("
            + std::to_string(i) + "," + std::to_string(j)
            + "), expected :(" + std::to_string(rows) + "," + std::to_string(colomns) + ")");
    return _m[i * colomns + j];
}
