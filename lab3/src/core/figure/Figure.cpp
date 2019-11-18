// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <algorithm>
#include <cmath>

#include "Figure.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

Figure::Figure(Figures f, Vector3f eye)
    : original(f)
    , changed(f.size())
    , visible(f.size(), false)
    , inside()
    , changed_inside()
    , m(Sh(1))
    , normals()
    , eye(eye)
{
    CalcInside();
}

void Figure::SetFigures(Figures _new)
{
    original = _new;
    changed.resize(original.size());
    visible.resize(original.size());

    CalcInside();
    ChangeColor();
    LoadMatrix(m);
}

void Figure::CalcInside()
{
    inside = { 0, 0, 0 };
    size_t size = 0;
    for (const auto& i : original)
        for (const auto& j : i) {
            ++size;
            inside += j;
        }
    inside /= static_cast<float>(size);
}

void Figure::LoadMatrix(const Matrix& _m)
{
    this->m = _m;
    std::transform(original.begin(), original.end(), changed.begin(),
        [&](const Polygon& p) { return m * p; });
    changed_inside = m * inside;
    normals = Matrix{ changed, changed_inside };
    Sort();
}

void Figure::AppendMatrix(const Matrix& _m)
{
    changed_inside = _m * changed_inside;
    normals *= _m;
    for (auto& i : changed)
        i *= _m;
    Sort();
}

void Figure::Sort()
{
    Matrix view = Matrix{ { eye.x(), eye.y(), eye.z(), 0 }, 1, 4 } // point of view
        * normals;
    for (size_t i = 0; i < changed.size(); ++i) {
        visible[i] = view[i] > 0;
        // std::sort(changed[i].begin(), changed[i].end(),
        //     [](const Vector3f& l, const Vector3f& r) -> bool { return l.y() < r.y(); });
    }
}

std::pair<Vector2f, Vector2f> Figure::MinMax() const
{
    if (original.empty())
        throw std::range_error("Figures are not initialized!!!");
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
            static_cast<float>(rand()) / mx //
        );
}
