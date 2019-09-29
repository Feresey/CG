#include "Polygon.hpp"

Polygon::Polygon(int size)
    : points(size)
{
}

Polygon::Polygon(const QVector<QVector3D>& points)
    : points(points)
{
}

QVector<QPointF> Polygon::display(QVector3D eye)
{
    QVector<QPointF> result;
    result.reserve(points.size());

    for (auto i : points)
        result.push_back({});
    return result;
}
