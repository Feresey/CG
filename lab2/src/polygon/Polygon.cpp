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

float Polygon::max_distance() const
{
    return std::max_element(figurePoints.begin(), figurePoints.end(),
        [](const QVector3D& l, const QVector3D& r) { return l.z() < r.z(); })->z();
}

void Polygon::setColor(QVector3D col) { color = col; }
float Polygon::r() const { return color.x(); }
float Polygon::g() const { return color.y(); }
float Polygon::b() const { return color.z(); }

Polygon::Points::iterator Polygon::begin() { return figurePoints.begin(); }
Polygon::Points::iterator Polygon::end() { return figurePoints.end(); }

Polygon::Points::const_iterator Polygon::cbegin() const { return figurePoints.cbegin(); }
Polygon::Points::const_iterator Polygon::cend() const { return figurePoints.cend(); }

size_t Polygon::size() const { return figurePoints.size(); }

QVector3D& Polygon::operator[](size_t index) { return figurePoints[index]; }
QVector3D Polygon::operator[](size_t index) const { return figurePoints[index]; }