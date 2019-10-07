#include <numeric>

#include "Polygon.hpp"

Polygon::Polygon(Points src, QVector3D col)
    : figurePoints(src)
{
    color[0] = col[0];
    color[1] = col[1];
    color[2] = col[2];
}

Polygon::Polygon(std::initializer_list<QVector3D> list)
    : Polygon()
{
    for (auto i : list)
        figurePoints.push_back(i);
}

// float Polygon::max() const
// {
//     return std::max_element(figurePoints.begin(), figurePoints.end(),
//         [](const QVector3D& l, const QVector3D& r) { return l.z() < r.z(); })
//         ->z();
// }

// float Polygon::min() const
// {
//     return std::min_element(figurePoints.begin(), figurePoints.end(),
//         [](const QVector3D& l, const QVector3D& r) { return l.z() < r.z(); })
//         ->z();
// }

void Polygon::setColor(QVector3D col)
{
    color[0] = col.x();
    color[1] = col.y();
    color[2] = col.z();
}

float* Polygon::getColor() { return color; }

Polygon::Points::iterator Polygon::begin() { return figurePoints.begin(); }
Polygon::Points::iterator Polygon::end() { return figurePoints.end(); }

Polygon::Points::const_iterator Polygon::cbegin() const { return figurePoints.cbegin(); }
Polygon::Points::const_iterator Polygon::cend() const { return figurePoints.cend(); }

size_t Polygon::size() const { return figurePoints.size(); }

QVector3D& Polygon::operator[](size_t index) { return figurePoints[index]; }
QVector3D Polygon::operator[](size_t index) const { return figurePoints[index]; }

#include <iostream>

std::ostream& operator<<(std::ostream& os, const QVector3D& src)
{
    os << src[0] << " " << src[1] << " " << src[2];
    return os;
}

bool Polygon::operator<(const Polygon& other) const
{
    float mx = 0;
    for (auto i : figurePoints)
        for (auto j : other.figurePoints) {
            float tmp = i.z() - j.z();
            if (abs(tmp) > abs(mx)) {
                mx = tmp;
            }
        }
    return mx > 0;
    // std::vector<float> anus;
    // for (auto i : figurePoints) {
    //     bool ind = true;
    //     for (auto j : other.figurePoints)
    //         if (i.distanceToPoint(j) < 0.0001f)
    //             ind = false;
    //     if (ind) {
    //         // float tmp[] = {
    //         //     i.x() - other[0].x(), i.y() - other[0].y(), i.z() - other[0].z(),
    //         //     other[1].x() - other[0].x(), other[1].y() - other[0].y(), other[1].z() - other[0].z(),
    //         //     other[2].x() - other[0].x(), other[2].y() - other[0].y(), other[2].z() - other[0].z() //
    //         // };
    //         // float pr = (tmp[0] * tmp[4] * tmp[8]
    //         //                + tmp[1] * tmp[5] * tmp[6]
    //         //                - tmp[0] * tmp[5] * tmp[7]
    //         //                - tmp[8] * tmp[1] * tmp[3])
    //         //     / (tmp[3] * tmp[7] - tmp[4] * tmp[6]);
    //         // std::cout << i << ":" << pr << " ; " << i. distanceToPlane(other[0], other[1], other[2]) << std::endl;
    //         return (i[2] - other[0][2]) > 0.0f;
    //     }
    // }
    // std::cout << figurePoints.size() << " : ";
    // for (auto i : anus)
    //     std::cout << i << ' ';
    // std::cout << std::endl;
    // return std::accumulate(anus.begin(), anus.end(), 0.0f);
}

std::ostream& operator<<(std::ostream& os, const Polygon& src)
{
    os.precision(2);
    // os << "max = " << src.max() << "; min = " << src.min();
    for (auto& point : src.figurePoints)
        os << point.x() << " " << point.y() << " " << point.z() << "; ";
    return os;
}
