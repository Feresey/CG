#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iterator>
#include <vector>

#include "Matrix.hpp"
#include "Vector.hpp"
#include "config.hpp"

class Polygon;

class Figure {
    using Figures = std::vector<Polygon>;
    Figures original;
    Figures changed;
    std::vector<bool> visible;
    Vector3f inside;
    Vector3f changed_inside;

    Matrix normals;
    Vector3f eye;

    void CalcInside();
    void Sort();

    class Iter : public std::iterator<std::forward_iterator_tag, Polygon> {
        using bit_iterator = std::vector<bool>::const_iterator;
        Figures::iterator fig_start;
        const Figures::iterator fig_end;
        bit_iterator vis;

    public:
        Iter(Figures::iterator f_start, const Figures::iterator f_end, bit_iterator v);
        Iter(Figures::iterator f_start, bit_iterator v);
        reference operator*();
        value_type operator*() const;
        reference operator->();
        value_type operator->() const;
        Iter& operator++();

        bool operator==(const Iter& other);
        bool operator!=(const Iter& other);
    };

public:
    Figure(Figures f = {}, Vector3f eye = { 0, 0, 1 });

    void SetFigures(const Figures& _new);
    void ChangeColor();
    void LoadMatrix(const Matrix& m);
    void AppendMatrix(const Matrix& m);

    std::pair<std::pair<float, float>, std::pair<float, float>> MinMax() const;
    Iter begin();
    Iter end();
};

Figure GenCylinder(float height, float radius, int approx);

#endif