#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <QVector3D>

#include <algorithm>
#include <vector>

class Polygon {
    using Points = std::vector<QVector3D>;
    Points figurePoints;
    QVector3D color;

public:
    Polygon(Points src = {},
        QVector3D color = QVector3D{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) });
    Polygon(std::initializer_list<QVector3D> list);

    float max_distance() const;
    void setColor(QVector3D col);
    float r() const;
    float g() const;
    float b() const;

    Points::iterator begin();
    Points::iterator end();
    Points::const_iterator cbegin() const;
    Points::const_iterator cend() const;

    size_t size() const;
    QVector3D& operator[](size_t index);
    QVector3D operator[](size_t index) const;
};

#endif /* POLYGON_HPP */