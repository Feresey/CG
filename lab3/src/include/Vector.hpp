#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <initializer_list>

template <class T, size_t S>
class Vector {
protected:
    T v[S];

public:
    Vector();
    Vector(std::initializer_list<T>);

    T& operator[](size_t pos);
    T operator[](size_t pos) const;

    Vector& operator+=(const Vector& r);
    Vector& operator-=(const Vector& r);
    Vector& operator*=(T);
    Vector& operator/=(T);

    Vector operator+(const Vector& r) const;
    Vector operator-(const Vector& r) const;
    Vector operator*(T) const;
    Vector operator/(T) const;
};

class Vector2i : public Vector<int, 2> {
public:
    Vector2i(std::initializer_list<int> L);
    Vector2i(const Vector<int, 2>& src);
    int& x();
    int& y();
};

class Vector3i : public Vector<int, 3> {
public:
    Vector3i(std::initializer_list<int> L);
    Vector3i(const Vector<int, 3>& src);
    int& x();
    int& y();
    int& z();
};

class Vector2f : public Vector<float, 2> {
public:
    Vector2f(std::initializer_list<float> L);
    Vector2f(const Vector<float, 2>& src);
    float& x();
    float& y();
};

class Vector3f : public Vector<float, 3> {
public:
    Vector3f(std::initializer_list<float> L);
    Vector3f(const Vector<float, 3>& src);
    float& x();
    float& y();
    float& z();

    float x() const;
    float y() const;
    float z() const;
};

#endif