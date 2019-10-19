#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <initializer_list>

template <class T, size_t S>
class Vector {
    T v[S];

public:
    Vector();
    Vector(std::initializer_list<T>);
    ~Vector();

    T& operator[](size_t pos);
    T operator[](size_t pos) const;
    T x() const;
    T y() const;
    T z() const;

    Vector& operator+=(const Vector& r);
    Vector& operator-=(const Vector& r);
    Vector& operator*=(T);
    Vector& operator/=(T);

    Vector operator+(const Vector& r) const;
    Vector operator-(const Vector& r) const;
    Vector operator*(T) const;
    Vector operator/(T) const;
};

typedef Vector<float, 3> Vector3f;
typedef Vector<int, 3> Vector3i;
typedef Vector<float, 2> Vector2f;
typedef Vector<int, 2> Vector2i;

#endif