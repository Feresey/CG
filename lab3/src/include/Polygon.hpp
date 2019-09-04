#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cmath>
#include <vector>

#include "Vector.hpp"

class Matrix;

class Polygon {
    using Points = std::vector<Vector3f>;
    Points points;
    Vector3f color, normal, center;
    std::vector<Polygon> split_recursive(const Points& src, size_t from, size_t to, Vector3f& col) const;
    void calcNormal();
    void calcCenter();

public:
    Polygon(Points src = {}, Vector3f col = { 0, 0, 0 });
    Polygon(std::initializer_list<Vector3f> list);

    void setColor(Vector3f v);
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
    Polygon& operator*=(const Matrix& m);
    Polygon operator*(const Matrix& m) const;

    Vector3f min() const;
    Vector3f max() const;

    // std::vector<float> to_plane() const;
    std::vector<Polygon> to_triangles() const;
    const Vector3f& getNormal() const;
    const Vector3f& getCenter() const;
};

Polygon operator*(const Polygon& p, const Matrix& m);

#endif /* POLYGON_HPP */