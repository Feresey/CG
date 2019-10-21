#include <cmath>
#include <numeric>

#include "Matrix.hpp"
#include "Polygon.hpp"

Polygon::Polygon(Points src, Vector3f col)
    : points(src)
{
    color[0] = col[0];
    color[1] = col[1];
    color[2] = col[2];
}

Polygon::Polygon(std::initializer_list<Vector3f> list)
    : Polygon()
{
    for (auto i : list)
        points.push_back(i);
}

void Polygon::setColor(float col0, float col1, float col2)
{
    color[0] = col0;
    color[1] = col1;
    color[2] = col2;
}

const float* Polygon::getColor() const { return color; }

Polygon::Points::iterator Polygon::begin() { return points.begin(); }
Polygon::Points::iterator Polygon::end() { return points.end(); }

Polygon::Points::const_iterator Polygon::begin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::end() const { return points.cend(); }

Polygon::Points::const_iterator Polygon::cbegin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::cend() const { return points.cend(); }

size_t Polygon::size() const { return points.size(); }

Vector3f& Polygon::operator[](size_t index) { return points[index]; }
Vector3f Polygon::operator[](size_t index) const { return points[index]; }

Vector3f Polygon::min() const
{
    float a = points[0].x(),
          b = points[0].y(),
          c = points[0].z();
    for (const auto& i : points) {
        if (i.x() < a)
            a = i.x();
        if (i.y() < b)
            b = i.y();
        if (i.z() < c)
            c = i.z();
    }
    return { a, b, c };
}

Vector3f Polygon::max() const
{
    float a = points[0].x(),
          b = points[0].y(),
          c = points[0].z();
    for (const auto& i : points) {
        if (i.x() > a)
            a = i.x();
        if (i.y() > b)
            b = i.y();
        if (i.z() > c)
            c = i.z();
    }
    return { a, b, c };
}

std::vector<float> Polygon::to_plane() const
{
    std::vector<float> res(4, 0.0f);
    const Vector3f v1 = points[0] - points[1],
                   v2 = points[0] - points[2], p = points[0];

    res[0] = v1.y() * v2.z() - v2.y() * v1.z();
    res[1] = v1.z() * v2.x() - v2.z() * v1.x();
    res[2] = v1.x() * v2.y() - v2.x() * v1.y();
    res[3] = -(p.x() * res[0] + p.y() * res[1] + p.z() * res[2]);
    return res;
}

std::vector<Polygon> Polygon::to_triangles() const
{
    std::vector<Polygon> res;
    size_t size = points.size() - 1;
    for (size_t i = 1; i < size; ++i)
        res.push_back({ points[0], points[i], points[i + 1] });
    return res;
}

Polygon& Polygon::operator*=(const Matrix& m)
{
    for (auto& i : points)
        i = m * i;
    return *this;
}

Polygon Polygon::operator*(const Matrix& m) const { return Polygon(*this) *= m; }
