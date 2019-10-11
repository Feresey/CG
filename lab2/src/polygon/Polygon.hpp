#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <cmath>

#include <QVector3D>
#include <QVector2D>

class Polygon {
    using Points = std::vector<QVector3D>;
    Points points;
    float color[3];

public:
    Polygon(Points src = {},
        QVector3D color = QVector3D{ //
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) });
    Polygon(std::initializer_list<QVector3D> list);

    void setColor(QVector3D col);
    float* getColor();

    Points::iterator begin();
    Points::iterator end();

    Points::const_iterator begin() const;
    Points::const_iterator end() const;
    
    Points::const_iterator cbegin() const;
    Points::const_iterator cend() const;

    size_t size() const;
    QVector3D& operator[](size_t index);
    QVector3D operator[](size_t index) const;
    bool operator<(const Polygon& other) const;
    int cmp(const Polygon& other) const;

};

#endif /* POLYGON_HPP */