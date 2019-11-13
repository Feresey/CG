// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <algorithm>
#include <cmath>

#include "Figure.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

Figure::Figure(Figures f)
    : original(f)
    , changed(f.size())
    , inside({ 0, 0, 0 })
    , changed_inside(inside)
{
    size_t size=0;
    for (const auto& i : f)
        for (const auto& j : i) {
            ++size;
            inside += j;
        }
    inside /= static_cast<float>(size);
}

void Figure::LoadMatrix(const Matrix& m)
{
    changed.resize(original.size());
    changed_inside = m * inside;
    std::transform(original.begin(), original.end(), changed.begin(),
        [m](const Polygon& p) { return m * p; });
}

void Figure::AppendMatrix(const Matrix& m)
{
    std::for_each(changed.begin(), changed.end(),
        [m](Polygon& p) { p = m * p; });
}

void Figure::Sort(const Vector3f& eye)
{
    Matrix view = Matrix{ { eye.x(), eye.y(), eye.z(), 0 }, 1, 4 } // point of view
        * Matrix{ changed, changed_inside }; // matrix of normals
    size_t size = 0;
    for (size_t i = 0; i < changed.size(); ++i)
        if (view[i] > 0)
            changed[size++] = changed[i];

    changed.resize(size);
}

std::pair<Vector2f, Vector2f> Figure::MinMax() const
{
    float min_x = changed[0][0][0], max_x = min_x,
          min_y = min_x, max_y = min_x;
    for (const auto& i : changed)
        for (const auto& j : i) {
            if (j[0] > max_x)
                max_x = j[0];
            if (j[1] > max_y)
                max_y = j[1];

            if (j[0] < min_x)
                min_x = j[0];
            if (j[1] < min_y)
                min_y = j[1];
        }
    return { { min_x, min_y }, { max_x, max_y } };
}

void Figure::ChangeColor()
{
    const float mx = static_cast<float>(RAND_MAX);
    for (auto& i : original)
        i.setColor(
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx);
}

Figure::Figures::iterator Figure::begin() { return changed.begin(); }
Figure::Figures::iterator Figure::end() { return changed.end(); }
Figure::Figures::const_iterator Figure::begin() const { return changed.cbegin(); }
Figure::Figures::const_iterator Figure::end() const { return changed.cend(); }
Figure::Figures::const_iterator Figure::cbegin() const { return changed.cbegin(); }
Figure::Figures::const_iterator Figure::cend() const { return changed.cend(); }
