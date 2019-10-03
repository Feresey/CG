#include "Polygon.hpp"

Polygon::Polygon(Points src, QVector3D color)
    : figurePoints(src)
    , color(color)
{
}

Polygon::Polygon(std::initializer_list<QVector3D> list)
    : Polygon()
{
    for (auto i : list)
        figurePoints.push_back(i);
}

float Polygon::max_distance(const QVector3D& point) const
{
    float res = 0;
    for (auto i : figurePoints)
        res += point.distanceToPoint(i);

    return res / figurePoints.size();
}

void Polygon::setColor(QVector3D col) { color = col; }
float Polygon::r() const { return color.x(); }
float Polygon::g() const { return color.y(); }
float Polygon::b() const { return color.z(); }

Polygon::Points::const_iterator Polygon::begin() const { return figurePoints.cbegin(); }
Polygon::Points::const_iterator Polygon::end() const { return figurePoints.cend(); }

size_t Polygon::size() const { return figurePoints.size(); }

QVector3D& Polygon::operator[](size_t index) { return figurePoints[index]; }
QVector3D Polygon::operator[](size_t index) const { return figurePoints[index]; }