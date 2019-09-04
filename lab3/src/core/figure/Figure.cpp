// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <algorithm>
#include <cmath>

#include "Figure.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

Figure::Figure(Figures f, Vector3f eye)
    : original()
    , changed()
    , visible()
    , inside()
    , changed_inside()
    , normals()
    , eye(eye)
{
    SetFigures(f);
}

void Figure::SetFigures(const Figures& _new)
{
    if (_new.empty())
        return;
    original.reserve(_new.size() * 2);
    original.resize(0);
    for (const auto& i : _new)
        for (auto& tr : i.to_triangles())
            original.push_back(tr);
    CalcInside();

    changed.resize(original.size());
    visible.resize(original.size());

    normals = Matrix(4, original.size());
    LoadMatrix(Sh(1));
}

void Figure::CalcInside()
{
    inside = Vector3f{ 0, 0, 0 };
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
    std::transform(original.begin(), original.end(), changed.begin(),
        [&](const Polygon& p) { return _m * p; });
    changed_inside = _m * inside;

    for (size_t i = 0; i < changed.size(); ++i) {
        const Vector3f& tmp(changed[i].getNormal());
        float d(-(tmp[0] * changed[i][0][0] + tmp[1] * changed[i][0][1] + tmp[2] * changed[i][0][2])),
            frac = 1;
        if ((tmp[0] * changed_inside[0] + tmp[1] * changed_inside[1] + tmp[2] * changed_inside[2] + d) > 0.0f) {
            frac = -1;
        } else {
            std::reverse(original[i].begin(), original[i].end());
            std::reverse(changed[i].begin(), changed[i].end());
        }
        normals(0, i) = tmp[0] * frac;
        normals(1, i) = tmp[1] * frac;
        normals(2, i) = tmp[2] * frac;
        normals(3, i) = d * frac;
    }

    Sort();
}

void Figure::AppendMatrix(const Matrix& _m)
{
    // changed_inside = _m * changed_inside;
    // normals = Matrix{ changed, changed_inside };

    for (auto& i : changed)
        i *= _m;
    Sort();
}

void Figure::Sort()
{
    for (size_t i = 0; i < changed.size(); ++i)
        visible[i] = (eye[0] * normals(0, i) + eye[1] * normals(1, i) + eye[2] * normals(2, i)) > 0;
}

std::pair<std::pair<float, float>, std::pair<float, float>> Figure::MinMax() const
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
        i.setColor({
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx //
        });
}
