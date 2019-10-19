#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <QVector2D>
#include <QVector3D>
#include <QPointF>

#include <vector>

class Polygon;

class Matrix {
    size_t rows, colomns;
    std::vector<float> _m;

public:
    Matrix(size_t N, size_t M);
    Matrix(const std::vector<float>& m, size_t N, size_t M);
    Matrix(const std::vector<Polygon> & src, const QVector3D& inside);

    Matrix operator*(const Matrix& second) const;
    Matrix& operator*=(const Matrix& second);

    Matrix& operator*=(float prod);
    Matrix operator*(float prod)const;
    
    Polygon operator*(const Polygon& v) const;
    QVector3D operator*(const QVector3D& v) const;

    float operator[](size_t i) const;
    float& operator[](size_t i);
    float& operator()(size_t i, size_t j);
    float operator()(size_t i, size_t j) const;
};

Matrix Rx(float phi);
Matrix Ry(float theta);
Matrix Sh(float scale_x, float scale_y, float scale_z);
Matrix Sh(float scale_all);
Matrix Move(const QVector3D& delta);

#endif /* MATRIX_HPP */