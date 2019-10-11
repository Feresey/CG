#include <cmath>
#include <numeric>

#include "Polygon.hpp"

float EPS = 1e-4f;

Polygon::Polygon(Points src, QVector3D col)
    : points(src)
{
    color[0] = col[0];
    color[1] = col[1];
    color[2] = col[2];
}

Polygon::Polygon(std::initializer_list<QVector3D> list)
    : Polygon()
{
    for (auto i : list)
        points.push_back(i);
}

void Polygon::setColor(QVector3D col)
{
    color[0] = col.x();
    color[1] = col.y();
    color[2] = col.z();
}

const float* Polygon::getColor()
{
    shared_color[0] = color[0];
    shared_color[1] = color[1];
    shared_color[2] = color[2];
    return shared_color;
}

Polygon::Points::iterator Polygon::begin() { return points.begin(); }
Polygon::Points::iterator Polygon::end() { return points.end(); }

Polygon::Points::const_iterator Polygon::begin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::end() const { return points.cend(); }

Polygon::Points::const_iterator Polygon::cbegin() const { return points.cbegin(); }
Polygon::Points::const_iterator Polygon::cend() const { return points.cend(); }

size_t Polygon::size() const { return points.size(); }

QVector3D& Polygon::operator[](size_t index) { return points[index]; }
QVector3D Polygon::operator[](size_t index) const { return points[index]; }

// #include <iostream>

// std::ostream& operator<<(std::ostream& os, const QVector3D src)
// {
//     os << "(" << src[0] << ',' << src[1] << ',' << src[2] << ')';
//     return os;
// }

int Polygon::cmp(const Polygon& other) const
{
    // std::cout.precision(10);
    // for (auto i : (*this))
    //     std::cout << i << ' ';
    // std::cout << std::endl;
    // for (auto i : other)
    //     std::cout << i << ' ';
    // std::cout << std::endl;

    auto det = [](float a, float b, float c, float d) -> float {
        return a * d - b * c;
    };

    auto create_line = [](const QVector3D& l, const QVector3D& r) -> QVector3D {
        return {
            r.y() - l.y(),
            l.x() - r.x(),
            (l.y() - r.y()) * l.x() + (r.x() - l.x()) * l.y()
        };
    };

    auto create_perp = [](const QVector3D& l, const QVector3D& r) -> QVector3D {
        return {
            l.x() - r.x(),
            l.y() - r.y(),
            -(l.x() * l.x() - r.x() * r.x() + l.y() * l.y() - r.y() * r.y()) / 2.0f
        };
    };

    // point of intersection
    auto intersect = [det](const QVector3D& n, const QVector3D& m, QVector2D& res) -> bool {
        float zn = det(m.x(), m.y(), n.x(), n.y());
        if (abs(zn) < EPS)
            return false;
        res = QVector2D{
            -det(m.z(), m.y(), n.z(), n.y()) / zn,
            -det(m.x(), m.z(), n.x(), n.z()) / zn
        };
        return true;
    };

    // (x,y,r): (x,y) - circle coord, r - circle radius
    auto circle = [create_perp, intersect](const std::vector<QVector3D>& points) -> QVector3D {
        QVector3D p1 = create_perp(points[0], points[1]),
                  p2 = create_perp(points[0], points[2]);
        QVector2D point;
        if (intersect(p1, p2, point))
            return { point.x(), point.y(), (point - points[0].toVector2D()).length() };
        else
            return {};
    };

    auto in_triangle = [](const QVector3D& p, const std::vector<QVector3D>& points) -> bool {
        float a = (points[0].x() - p.x()) * (points[1].y() - points[0].y()) - (points[1].x() - points[0].x()) * (points[0].y() - p.y()),
              b = (points[1].x() - p.x()) * (points[2].y() - points[1].y()) - (points[2].x() - points[1].x()) * (points[1].y() - p.y()),
              c = (points[2].x() - p.x()) * (points[0].y() - points[2].y()) - (points[0].x() - points[2].x()) * (points[2].y() - p.y());
        return (a < 0.5f && b < 0.5f && c < 0.5f) || (a > -0.5f && b > -0.5f && c > -0.5f);
    };

    QVector3D circle_this = circle(points),
              circle_other = circle(other.points);

    // points of intersection for all lines and loacted into both circles
    std::vector<QVector2D> inter_lines;
    for (size_t i = 0; i < other.size(); ++i) {
        for (size_t j = i + 1; j < other.size(); ++j) {
            for (size_t l = 0; l < size(); ++l) {
                for (size_t k = l + 1; k < size(); ++k) {
                    QVector3D n = create_line(other[i], other[j]),
                              m = create_line((*this)[l], (*this)[k]);
                    QVector2D cross;
                    bool tmp = intersect(n, m, cross);
                    if (tmp
                        && (cross - circle_this.toVector2D()).length() < circle_this[2] + EPS
                        && (cross - circle_other.toVector2D()).length() < circle_other[2] + EPS
                        && in_triangle(cross.toVector3D(), points)
                        && in_triangle(cross.toVector3D(), other.points))
                        inter_lines.push_back(cross);
                }
            }
        }
    }

    for (auto i : (*this))
        if (in_triangle(i, other.points))
            inter_lines.push_back(i.toVector2D());
    for (auto i : other)
        if (in_triangle(i, points))
            inter_lines.push_back(i.toVector2D());

    // common points for both polygons
    std::vector<QVector2D> common_points;
    for (auto i : (*this)) {
        bool all = false;
        for (auto j : other) {
            QVector2D ii = i.toVector2D(),
                      jj = j.toVector2D(),
                      res = ii - jj;

            if (res.length() < EPS) {
                all = true;
                break;
            }
        }
        if (all)
            common_points.push_back(i.toVector2D());
    }

    std::vector<QVector2D> cross;
    for (auto i : inter_lines) {
        bool all = true;
        for (auto j : common_points)
            if ((i - j).length() < EPS)
                all = false;
        if (all)
            cross.push_back(i);
    }

    std::vector<float> diff;
    for (auto i : cross) {
        //normalize
        QVector3D norm1 = QVector3D::normal(points[0], points[1], points[2]),
                  norm2 = QVector3D::normal(other[0], other[1], other[2]);
        float p1 = points[0].z() - (norm1.x() * (i.x() - points[0].x()) + norm1.y() * (i.y() - points[0].y())) / norm1.z(),
              p2 = other[0].z() - (norm2.x() * (i.x() - other[0].x()) + norm2.y() * (i.y() - other[0].y())) / norm2.z(),
              pp = p2 - p1;
        diff.push_back(pp);
    }
    // std::cout << "points" << std::endl;
    // for (auto i : cross)
    //     std::cout << i << ' ';
    // std::cout << '\n';
    // std::cout << "diff" << std::endl;
    // for (auto i : diff)
    //     std::cout << i << ' ';
    // std::cout << '\n';
    if (diff.empty())
        return 0;
    return std::accumulate(diff.begin(), diff.end(), 0.0f) / static_cast<float>(diff.size()) > 0 ? 1 : -1;
}

bool Polygon::operator<(const Polygon& other) const
{
    return cmp(other) == -1;
}
