#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cmath>
#include <vector>

#include "Vector.hpp"

class Polygon {
    using Points = std::vector<Vector3f>;
    Points points;
    float color[3];

public:
    Polygon(Points src = {},
        Vector3f color = Vector3f{ //
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) });
    Polygon(std::initializer_list<Vector3f> list);

    void setColor(float col0, float col1, float col2);
    const float* getColor() const;

    Points::iterator begin();
    Points::iterator end();

    Points::const_iterator begin() const;
    Points::const_iterator end() const;

    Points::const_iterator cbegin() const;
    Points::const_iterator cend() const;

    size_t size() const;
    Vector3f& operator[](size_t index);
    Vector3f operator[](size_t index) const;

    Vector3f min() const;
    Vector3f max() const;

    std::vector<float> to_plane() const;
};

#endif /* POLYGON_HPP */