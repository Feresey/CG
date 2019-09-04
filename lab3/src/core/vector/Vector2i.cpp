// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Vector.hpp"

#include <cmath>
#include <stdexcept>

Vector2i::Vector2i(int x, int y)
{
    v[0] = x;
    v[1] = y;
}
Vector2i& Vector2i::operator+=(const Vector2i& r)
{
    v[0] += r.v[0];
    v[1] += r.v[1];
    return *this;
}
Vector2i& Vector2i::operator-=(const Vector2i& r)
{
    v[0] -= r.v[0];
    v[1] -= r.v[1];
    return *this;
}
Vector2i& Vector2i::operator*=(int num)
{
    v[0] *= num;
    v[1] *= num;
    return *this;
}
Vector2i& Vector2i::operator/=(int num)
{
    v[0] /= num;
    v[1] /= num;
    return *this;
}
Vector2i& Vector2i::operator*=(float num)
{
    v[0] = float_to_int(num * float(v[0]));
    v[1] = float_to_int(num * float(v[1]));
    return *this;
}
Vector2i& Vector2i::operator/=(float num)
{
    v[0] = float_to_int(float(v[0]) / num);
    v[1] = float_to_int(float(v[1]) / num);
    return *this;
}

Vector2i Vector2i::operator+(const Vector2i& r) const { return Vector2i(*this) += r; }
Vector2i Vector2i::operator-(const Vector2i& r) const { return Vector2i(*this) -= r; }
Vector2i Vector2i::operator*(float num) const { return Vector2i(*this) *= num; }
Vector2i Vector2i::operator/(float num) const { return Vector2i(*this) /= num; }

int Vector2i::operator[](size_t pos) const { return v[pos]; }
int& Vector2i::operator[](size_t pos) { return v[pos]; }

int& Vector2i::x() { return v[0]; }
int& Vector2i::y() { return v[1]; }

int Vector2i::x() const { return v[0]; }
int Vector2i::y() const { return v[1]; }