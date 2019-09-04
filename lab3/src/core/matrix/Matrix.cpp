// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//V_LEVEL_3::773
#include <algorithm>
#include <iomanip>
#include <stdexcept>

#include "Matrix.hpp"
#include "Polygon.hpp"

Matrix::Matrix(size_t rows, size_t colomns)
    : rows(rows)
    , colomns(colomns)
    , _m(rows * colomns, 0.0f)
{
}

Matrix::Matrix(const std::vector<float>& m, size_t rows, size_t colomns)
    : rows(rows)
    , colomns(colomns)
    , _m(m)
{
    if (m.size() != rows * colomns)
        throw std::invalid_argument("Matrix size must be equal to rows*colomns : " + std::to_string(rows * colomns));
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

Vector3f Matrix::operator*(const Vector3f& v) const
{
    Matrix tmp = Matrix{ { v.x(), v.y(), v.z(), 1 }, 1, 4 } * (*this);
    return Vector3f{
        tmp[0] / tmp[3],
        tmp[1] / tmp[3],
        tmp[2] / tmp[3]
    };
}

Polygon Matrix::operator*(const Polygon& v) const { return Polygon(v) *= *this; }

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

Matrix& Matrix::operator*=(float prod)
{
    std::transform(_m.begin(), _m.end(), _m.begin(),
        [prod](float var) { return var * prod; });
    return *this;
}

Matrix Matrix::operator*(float prod) const { return Matrix{ *this } *= prod; }

bool Matrix::empty() const { return rows * colomns == 0; }

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.colomns; ++j)
            os << std::setw(10) << std::right << m(i, j) << " ";
        os << std::endl;
    }
    return os;
}