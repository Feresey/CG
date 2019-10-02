#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <QPointF>
#include <QVector3D>

#include <array>

template <size_t N = 4>
class Matrix {
    std::array<double, N * N> _m;

public:
    Matrix()
        : _m()
    {
        _m.fill(0);
        for (size_t i = 0; i < N; ++i)
            _m[i + N * i] = 1;
    }

    Matrix(std::array<double, N * N> m)
        : _m(m)
    {
    }

    const Matrix& operator*(const Matrix& second)
    {
        std::array<double, N * N> tmp;
        tmp.fill(0);
        for (i = 0; i < N; ++i)
            for (j = 0; j < N; ++j)
                for (k = 0; k < N; ++k)
                    tmp[i + N * j] += _m[i + N * k] * second[k + N * j];
        _m = tmp;
        return _m;
    }

    QPointF operator*(const QVector3D& v)
    {

    }
};

#endif /* MATRIX_HPP */