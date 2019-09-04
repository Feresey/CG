// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Vector.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

Vector3f::Vector3f(float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

//logic
Vector3f& Vector3f::operator+=(const Vector3f& r)
{
    v[0] += r.v[0];
    v[1] += r.v[1];
    v[2] += r.v[2];
    return *this;
}
Vector3f& Vector3f::operator-=(const Vector3f& r)
{
    v[0] -= r.v[0];
    v[1] -= r.v[1];
    v[2] -= r.v[2];
    return *this;
}
Vector3f Vector3f::CrossProduct(const Vector3f& v2) const
{
    return { v[1] * v2.v[2] - v[2] * v2.v[1],
        v[2] * v2.v[0] - v[0] * v2.v[2],
        v[0] * v2.v[1] - v[1] * v2.v[0] };
}

float Vector3f::DotProduct(const Vector3f& r) const { return v[0] * r[0] + v[1] * r[1] + v[2] * r[2]; }
float Vector3f::Angle(const Vector3f& r) const { return DotProduct(r) / Length() / r.Length(); }

Vector3f Vector3f::operator+(const Vector3f& r) const { return Vector3f(*this) += r; }
Vector3f Vector3f::operator-(const Vector3f& r) const { return Vector3f(*this) -= r; }
Vector3f Vector3f::operator-() const { return Vector3f(*this) *= -1; }

Vector3f& Vector3f::operator*=(float num)
{
    v[0] *= num;
    v[1] *= num;
    v[2] *= num;
    return *this;
}
Vector3f& Vector3f::operator/=(float num)
{
    v[0] /= num;
    v[1] /= num;
    v[2] /= num;
    return *this;
}
Vector3f& Vector3f::operator-=(float num)
{
    v[0] -= num;
    v[1] -= num;
    v[2] -= num;
    return *this;
}
Vector3f& Vector3f::operator+=(float num)
{
    v[0] += num;
    v[1] += num;
    v[2] += num;
    return *this;
}
Vector3f operator*(const Vector3f& orig, float num)
{
    return Vector3f(
        orig.v[0] * num,
        orig.v[1] * num,
        orig.v[2] * num);
}
Vector3f operator*(float num, const Vector3f& orig)
{
    return Vector3f(
        orig.v[0] * num,
        orig.v[1] * num,
        orig.v[2] * num);
}
Vector3f operator/(const Vector3f& orig, float num)
{
    return Vector3f(
        orig.v[0] / num,
        orig.v[1] / num,
        orig.v[2] / num);
}
Vector3f operator/(float num, const Vector3f& orig)
{
    return Vector3f(
        orig.v[0] / num,
        orig.v[1] / num,
        orig.v[2] / num);
}
Vector3f operator-(const Vector3f& orig, float num)
{
    return Vector3f(
        orig.v[0] - num,
        orig.v[1] - num,
        orig.v[2] - num);
}
Vector3f operator-(float num, const Vector3f& orig)
{
    return Vector3f(
        orig.v[0] - num,
        orig.v[1] - num,
        orig.v[2] - num);
}
Vector3f operator+(const Vector3f& orig, float num)
{
    return Vector3f(
        orig.v[0] + num,
        orig.v[1] + num,
        orig.v[2] + num);
}
Vector3f operator+(float num, const Vector3f& orig)
{
    return Vector3f(
        orig.v[0] + num,
        orig.v[1] + num,
        orig.v[2] + num);
}

float operator*(const Vector3f& l, const Vector3f& r) { return l.DotProduct(r); }

float& Vector3f::operator[](size_t pos) { return v[pos]; }
float Vector3f::operator[](size_t pos) const { return v[pos]; }

float& Vector3f::x() { return v[0]; }
float& Vector3f::y() { return v[1]; }
float& Vector3f::z() { return v[2]; }

float Vector3f::x() const { return v[0]; }
float Vector3f::y() const { return v[1]; }
float Vector3f::z() const { return v[2]; }

float Vector3f::Length() const { return DistanceTo({}); }
float Vector3f::DistanceTo(const Vector3f& v) const
{
    Vector3f tmp(*this - v);
    auto pow2 = [](float num) -> float { return num * num; };
    return sqrtf(pow2(tmp[0]) + pow2(tmp[1]) + pow2(tmp[2]));
}

void Vector3f::Normalize() { *this /= Length(); }

std::ostream& operator<<(std::ostream& os, const Vector3f& v)
{
    os << '(' << v[0] << ',' << v[1] << ',' << v[2] << ')';
    return os;
}
