#include <cmath>
#include <numeric>

#include "Polygon.hpp"

float EPS = 1e-9f;

Polygon::Polygon(Points src, QVector3D col)
    : points(src)
{
    // if (src.size() < 3)
    //     throw std::invalid_argument("Polygon must have 3 points, given: " + std::to_string(src.size()));
    color[0] = col[0];
    color[1] = col[1];
    color[2] = col[2];
}

Polygon::Polygon(std::initializer_list<QVector3D> list)
    : Polygon()
{
    for (auto i : list)
        points.push_back(i);
}

void Polygon::setColor(QVector3D col)
{
    color[0] = col.x();
    color[1] = col.y();
    color[2] = col.z();
}

const float* Polygon::getColor() const { return color; }

Polygon::Points::iterator Polygon::begin() { return points.begin(); }
Polygon::Points::iterator Polygon::end() { return points.end(); }

Polygon::Points::const_iterator Polygon::begin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::end() const { return points.cend(); }

Polygon::Points::const_iterator Polygon::cbegin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::cend() const { return points.cend(); }

size_t Polygon::size() const { return points.size(); }

QVector3D& Polygon::operator[](size_t index) { return points[index]; }
QVector3D Polygon::operator[](size_t index) const { return points[index]; }

QVector3D Polygon::min() const
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

QVector3D Polygon::max() const
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
    const QVector3D v1 = points[0] - points[1],
                    v2 = points[0] - points[2], p = points[0];

    res[0] = v1.y() * v2.z() - v2.y() * v1.z();
    res[1] = v1.z() * v2.x() - v2.z() * v1.x();
    res[2] = v1.x() * v2.y() - v2.x() * v1.y();
    res[3] = -(p.x() * res[0] + p.y() * res[1] + p.z() * res[2]);
    return res;
}
