#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <iostream>

struct Vector3f {
    float v[3];

    Vector3f(float x = 0, float y = 0, float z = 0);

    float& operator[](size_t pos);
    float operator[](size_t pos) const;
    float& x();
    float& y();
    float& z();
    float x() const;
    float y() const;
    float z() const;

    float DotProduct(const Vector3f& r) const;
    float Length() const;
    float DistanceTo(const Vector3f& v) const;
    float Angle(const Vector3f& r) const;
    void Normalize();

    Vector3f& operator+=(const Vector3f& r);
    Vector3f& operator-=(const Vector3f& r);
    Vector3f operator+(const Vector3f& r) const;
    Vector3f operator-(const Vector3f& r) const;
    Vector3f operator-() const;
    Vector3f CrossProduct(const Vector3f& r) const;

    Vector3f& operator*=(float);
    Vector3f& operator/=(float);
    Vector3f& operator+=(float);
    Vector3f& operator-=(float);

    friend Vector3f operator*(const Vector3f& orig, float);
    friend Vector3f operator*(float, const Vector3f&);
    friend Vector3f operator/(const Vector3f& orig, float);
    friend Vector3f operator/(float, const Vector3f&);
    friend Vector3f operator+(const Vector3f& orig, float);
    friend Vector3f operator+(float, const Vector3f&);
    friend Vector3f operator-(const Vector3f& orig, float);
    friend Vector3f operator-(float, const Vector3f&);
    friend float operator*(const Vector3f& l, const Vector3f& r);

    friend std::ostream& operator<<(std::ostream& os, const Vector3f& v);
};

class Vector2i {
public:
    int v[2];

    Vector2i(int x = 0, int y = 0);

    int& operator[](size_t pos);
    int operator[](size_t pos) const;

    Vector2i& operator+=(const Vector2i& r);
    Vector2i& operator-=(const Vector2i& r);
    Vector2i& operator*=(int);
    Vector2i& operator/=(int);

    Vector2i operator+(const Vector2i& r) const;
    Vector2i operator-(const Vector2i& r) const;
    Vector2i operator*(int)const;
    Vector2i operator/(int) const;

    Vector2i& operator*=(float);
    Vector2i& operator/=(float);

    Vector2i operator*(float)const;
    Vector2i operator/(float) const;

    int& x();
    int& y();
    int x() const;
    int y() const;
};

constexpr inline int float_to_int(float d) { return d >= 0.0f ? int(d + 0.5f) : int(d - float(int(d - 1)) + 0.5f) + int(d - 1); }

#endif