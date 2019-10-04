#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <QVector2D>
#include <QVector3D>

#include <vector>

#include "Polygon.hpp"

class Matrix {
    size_t N, M;
    std::vector<float> _m;

public:
    Matrix(size_t N, size_t M);
    Matrix(std::vector<float> m, size_t N, size_t M);

    Matrix operator*(const Matrix& second) const;
    Matrix& operator*=(const Matrix& second);
    QVector3D operator*(const QVector3D& v) const;
    Polygon operator*(const Polygon& v) const;
    QVector2D projection(const QVector3D& point) const;

    float operator[](size_t i) const;
    float& operator[](size_t i);
};

#endif /* MATRIX_HPP */