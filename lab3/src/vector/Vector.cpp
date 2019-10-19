#include <stdexcept>

#include "Vector.hpp"

template <class T, size_t S>
Vector<T, S>::Vector()
{
    for (size_t i = 0; i < S; ++i)
        v[i] = T();
}

template <class T, size_t S>
Vector<T, S>::Vector(std::initializer_list<T> list)
{
    if (list.size() != S)
        throw std::invalid_argument("arguments size does not match to class capacity");
    size_t ins = 0;
    for (auto i : list)
        v[ins++] = i;
}

template <class T, size_t S>
Vector<T, S>::~Vector()
{
}

template <class T, size_t S>
T& Vector<T, S>::operator[](size_t pos)
{
    if (pos >= S)
        throw std::invalid_argument("bad position");
    return v[pos];
}

template <class T, size_t S>
T Vector<T, S>::operator[](size_t pos) const
{
    if (pos >= S)
        throw std::invalid_argument("bad position");
    return v[pos];
}

template <class T, size_t S>
T Vector<T, S>::x() const
{
    if constexpr (S < 1)
        throw std::logic_error("class capacity does not match");
    return v[0];
}

template <class T, size_t S>
T Vector<T, S>::y() const
{
    if constexpr (S < 3)
        throw std::logic_error("class capacity does not match");
    return v[1];
}

template <class T, size_t S>
T Vector<T, S>::z() const
{
    if constexpr (S < 3)
        throw std::logic_error("class capacity does not match");
    return v[2];
}

template <class T, size_t S>
Vector<T, S>& Vector<T, S>::operator+=(const Vector<T, S>& r)
{
    for (size_t i = 0; i < S; ++i)
        v[i] += r[i];
    return *this;
}

template <class T, size_t S>
Vector<T, S>& Vector<T, S>::operator-=(const Vector<T, S>& r)
{
    for (size_t i = 0; i < S; ++i)
        v[i] -= r[i];
    return *this;
}

template <class T, size_t S>
Vector<T, S>& Vector<T, S>::operator*=(T val)
{
    for (size_t i = 0; i < S; ++i)
        v[i] *= val;
    return *this;
}

template <class T, size_t S>
Vector<T, S>& Vector<T, S>::operator/=(T val)
{
    for (size_t i = 0; i < S; ++i)
        v[i] /= val;
    return *this;
}

template <class T, size_t S>
Vector<T, S> Vector<T, S>::operator+(const Vector& r) const { return Vector(*this) += r; }
template <class T, size_t S>
Vector<T, S> Vector<T, S>::operator-(const Vector& r) const { return Vector(*this) -= r; }
template <class T, size_t S>
Vector<T, S> Vector<T, S>::operator*(T r) const { return Vector(*this) *= r; }
template <class T, size_t S>
Vector<T, S> Vector<T, S>::operator/(T r) const { return Vector(*this) /= r; }

template class Vector<float, 3>;
template class Vector<int, 3>;
template class Vector<float, 2>;
template class Vector<int, 2>;
