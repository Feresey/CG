#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <QPointF>
#include <QVector3D>

#include <vector>

class Matrix {
    size_t N, M;
    std::vector<float> _m;

public:
    Matrix(size_t N, size_t M);
    Matrix(std::vector<float> m, size_t N, size_t M);

    Matrix operator*(const Matrix& second) const;
    Matrix& operator*=(const Matrix& second);
    QVector3D operator*(const QVector3D& v) const;

    float operator[](size_t i) const;
    float& operator[](size_t i);
};

#endif /* MATRIX_HPP */