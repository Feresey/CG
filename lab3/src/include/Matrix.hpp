#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

class Vector3f;

#include "Polygon.hpp"

class Matrix {
    size_t rows, colomns;
    std::vector<float> _m;

public:
    Matrix(size_t rows = 0, size_t colomns = 0);
    Matrix(const std::vector<float>& m, size_t rows, size_t colomns);
    // Matrix(const std::vector<Polygon>& src, const Vector3f& inside);

    Matrix operator*(const Matrix& second) const;
    Matrix& operator*=(const Matrix& second);

    Matrix& operator*=(float prod);
    Matrix operator*(float prod) const;

    Polygon operator*(const Polygon& v) const;
    Vector3f operator*(const Vector3f& v) const;

    float operator[](size_t i) const;
    float& operator[](size_t i);
    float& operator()(size_t i, size_t j);
    float operator()(size_t i, size_t j) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    bool empty() const;
};

Matrix Rx(float alpha);
Matrix Ry(float beta);
Matrix Rz(float gamma);
Matrix Sh(float scale_x, float scale_y, float scale_z);
Matrix Sh(float scale_all);
Matrix Move(const Vector3f& delta);

#endif /* MATRIX_HPP */