// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Vector.h"

template class Vector<float, 3>;
template class Vector<int, 3>;
template class Vector<float, 2>;
template class Vector<int, 2>;

Vector2i::Vector2i(std::initializer_list<int> L)
    : Vector<int, 2>(L)
{
}
Vector2i::Vector2i(const Vector<int, 2>& src)
    : Vector<int, 2>(src)
{
}
int Vector2i::x() const { return v[0]; }
int Vector2i::y() const { return v[1]; }

Vector3i::Vector3i(std::initializer_list<int> L)
    : Vector<int, 3>(L)
{
}
Vector3i::Vector3i(const Vector<int, 3>& src)
    : Vector<int, 3>(src)
{
}
int Vector3i::x() const { return v[0]; }
int Vector3i::y() const { return v[1]; }
int Vector3i::z() const { return v[2]; }

Vector2f::Vector2f(std::initializer_list<float> L)
    : Vector<float, 2>(L)
{
}
Vector2f::Vector2f(const Vector<float, 2>& src)
    : Vector<float, 2>(src)
{
}
float Vector2f::x() const { return v[0]; }
float Vector2f::y() const { return v[1]; }

Vector3f::Vector3f(std::initializer_list<float> L)
    : Vector<float, 3>(L)
{
}
Vector3f::Vector3f(const Vector<float, 3>& src)
    : Vector<float, 3>(src)
{
}
float Vector3f::x() const { return v[0]; }
float Vector3f::y() const { return v[1]; }
float Vector3f::z() const { return v[2]; }
