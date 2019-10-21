#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <vector>

#include "Vector.hpp"
class Polygon;
class Matrix;

class Figure {
    using Figures = std::vector<Polygon>;
    Figures original;
    Figures changed;
    Vector3f inside;
    Vector3f changed_inside;

public:
    Figure(Figures f = {});

    void LoadMatrix(const Matrix& m);
    void Sort(const Vector3f& eye);
    std::pair<Vector2f, Vector2f> MinMax() const;
    void ChangeColor();
    Figures::iterator begin();
    Figures::iterator end();
    Figures::const_iterator begin() const;
    Figures::const_iterator end() const;
    Figures::const_iterator cbegin() const;
    Figures::const_iterator cend() const;
};

#endif