#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <QPointF>
#include <QVector3D>
#include <QVector>

class Polygon {
    QVector<QVector3D> points;

public:
    explicit Polygon(int num_points = 4);
    explicit Polygon(const QVector<QVector3D>& points);
    QVector<QPointF> display(QVector3D point);
};

#endif /*POLYGON_HPP*/