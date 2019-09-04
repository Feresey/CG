// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <cmath>
#include <numeric>
#include <queue>

#include "Matrix.hpp"
#include "Polygon.hpp"

Polygon::Polygon(Points src, Vector3f col)
    : points(src)
    , color(col)
    , normal()
    , center()
{
    calcNormal();
    calcCenter();
}

Polygon::Polygon(std::initializer_list<Vector3f> list)
    : Polygon()
{
    if (list.size() < 3)
        throw std::invalid_argument("Polygon must contains at least 3 points");

    for (auto i : list)
        points.push_back(i);
}

void Polygon::setColor(Vector3f v) { color = v; }

const float* Polygon::getColor() const { return color.v; }

Polygon::Points::iterator Polygon::begin() { return points.begin(); }
Polygon::Points::iterator Polygon::end() { return points.end(); }

Polygon::Points::const_iterator Polygon::begin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::end() const { return points.cend(); }

Polygon::Points::const_iterator Polygon::cbegin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::cend() const { return points.cend(); }

size_t Polygon::size() const { return points.size(); }

Vector3f& Polygon::operator[](size_t index) { return points[index]; }
Vector3f Polygon::operator[](size_t index) const { return points[index]; }

Polygon operator*(const Polygon& p, const Matrix& m) { return m * p; }

Vector3f Polygon::min() const
{
    float a = points[0][0],
          b = points[0][1],
          c = points[0][2];
    for (const auto& i : points) {
        if (i[0] < a)
            a = i[0];
        if (i[1] < b)
            b = i[1];
        if (i[2] < c)
            c = i[2];
    }
    return { a, b, c };
}

Vector3f Polygon::max() const
{
    float a = points[0][0],
          b = points[0][1],
          c = points[0][2];
    for (const auto& i : points) {
        if (i[0] > a)
            a = i[0];
        if (i[1] > b)
            b = i[1];
        if (i[2] > c)
            c = i[2];
    }
    return { a, b, c };
}

// std::vector<float> Polygon::to_plane() const
// {
//     if (points.size() < 3)
//         return { 0, 0, 0, 0 };
//     std::vector<float> res(4, 0.0f);
//     const Vector3f v1 = points[0] - points[1],
//                    v2 = points[0] - points[2], p = points[0];
//     res[0] = v1[1] * v2[2] - v2[1] * v1[2];
//     res[1] = v1[2] * v2[0] - v2[2] * v1[0];
//     res[2] = v1[0] * v2[1] - v2[0] * v1[1];
//     res[3] = -(p[0] * res[0] + p[1] * res[1] + p[2] * res[2]);
//     return res;
// }

std::vector<Polygon> Polygon::split_recursive(const std::vector<Vector3f>& src, size_t from, size_t to, Vector3f& col) const
{
    if (src.size() < 3)
        return {};
    std::vector<Polygon> res;
    std::queue<std::pair<size_t, size_t>> q;
    q.push({ from, to });
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        size_t center = (curr.second + curr.first) / 2;
        if (center == curr.first || center == curr.second)
            continue;
        col += 0.1f;
        res.push_back(Polygon{ { src[curr.first], src[center], src[curr.second] }, col });
        q.push({ curr.first, center });
        q.push({ center, curr.second });
    }
    return res;
}

std::vector<Polygon> Polygon::to_triangles() const
{
    Vector3f col;
    std::vector<Polygon> res;
    size_t step = size() / 3;
    res.push_back(Polygon{ points[0], points[step], points[step * 2] });

    auto one = split_recursive(points, 0, step, col);
    res.insert(res.end(), one.begin(), one.end());

    one = split_recursive(points, step, 2 * step, col);
    res.insert(res.end(), one.begin(), one.end());

    std::vector<Vector3f> last{ points.begin() + 2 * step, points.end() };
    last.push_back(points[0]);
    one = split_recursive(last, 0, last.size() - 1, col);
    res.insert(res.end(), one.begin(), one.end());
    return res;
}

Polygon& Polygon::operator*=(const Matrix& m)
{
    for (auto& i : points)
        i = m * i;
    calcNormal();
    calcCenter();
    return *this;
}

Polygon Polygon::operator*(const Matrix& m) const { return Polygon(*this) *= m; }

void Polygon::calcNormal()
{
    if (points.size() >= 3) {
        const Vector3f v1 = points[0] - points[1],
                       v2 = points[0] - points[2];
        normal[0] = v1[1] * v2[2] - v2[1] * v1[2];
        normal[1] = v1[2] * v2[0] - v2[2] * v1[0];
        normal[2] = v1[0] * v2[1] - v2[0] * v1[1];
        normal.Normalize();
    }
}

void Polygon::calcCenter()
{
    size_t count{ 0 };
    center[0] = center[1] = center[2] = 0;
    for (const auto& i : points) {
        center += i;
        ++count;
    }
    center /= static_cast<float>(count);
}

const Vector3f& Polygon::getNormal() const { return normal; }
const Vector3f& Polygon::getCenter() const { return center; }
