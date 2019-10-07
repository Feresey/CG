#include "Vector3I.hpp"

#include <cmath>

Vector3I::Vector3I(int x, int y, int z)
{
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
}

Vector3I::Vector3I(int coord[3])
    : Vector3I(coord[0], coord[1], coord[2])
{
}

Vector3I::Vector3I(const QVector3D& src)
    : Vector3I(static_cast<int>(src.x()), static_cast<int>(src.y()), static_cast<int>(src.z()))
{
}

Vector3I::Vector3I(const Vector3I& src)
    : Vector3I()
{
    (*this) = src;
}

Vector3I::Vector3I(Vector3I&& src)
    : Vector3I()
{
    (*this) = src;
}

Vector3I& Vector3I::operator=(const Vector3I& src)
{
    coord[0] = src[0];
    coord[1] = src[1];
    coord[2] = src[2];
    return *this;
}

Vector3I& Vector3I::operator=(Vector3I&& src)
{
    coord[0] = src[0];
    coord[1] = src[1];
    coord[2] = src[2];
    return *this;
}

int Vector3I::x() const { return coord[0]; }
int Vector3I::y() const { return coord[1]; }
int Vector3I::z() const { return coord[2]; }

int& Vector3I::operator[](size_t pos) { return coord[pos]; }
int Vector3I::operator[](size_t pos) const { return coord[pos]; }

Vector3I& Vector3I::operator+=(const Vector3I& src)
{
    coord[0] += src[0];
    coord[1] += src[1];
    coord[2] += src[2];
    return *this;
}

Vector3I& Vector3I::operator-=(const Vector3I& src)
{
    coord[0] -= src[0];
    coord[1] -= src[1];
    coord[2] -= src[2];
    return *this;
}

Vector3I& Vector3I::operator*=(float value)
{
    coord[0] = static_cast<int>(value * float(coord[0]));
    coord[1] = static_cast<int>(value * float(coord[1]));
    coord[2] = static_cast<int>(value * float(coord[2]));
    return *this;
}

Vector3I Vector3I::operator+(const Vector3I& src) const { return Vector3I(*this) += src; }
Vector3I Vector3I::operator-(const Vector3I& src) const { return Vector3I(*this) -= src; }
Vector3I Vector3I::operator*(float value) const { return Vector3I(*this) *= value; }

std::ostream& operator<<(std::ostream& os, const Vector3I& src)
{
    os << "(" << src[0] << ", " << src[1] << ", " << src[2] << ")";
    return os;
}
