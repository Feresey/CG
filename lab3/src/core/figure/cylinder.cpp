#include "Figure.hpp"

#include <algorithm>

Figure GenCylinder(float height, float radius, int approx)
{
    std::vector<Polygon> res;
    float
        step(360.f * D2R / static_cast<float>(approx)),
        curr(0),
        RPartSize(radius / float(approx)),
        HPartSize(height / float(approx));

    std::vector<Vector3f> circle;
    circle.reserve(static_cast<size_t>(approx));

    for (int i = 0; i < approx; ++i, curr += step)
        circle.push_back(Vector3f{ RPartSize * cosf(curr), RPartSize * sinf(curr), -height / 2 });

    const size_t size(circle.size());

    // central part
    {
        const Vector3f center(0, 0, -height / 2);
        res.push_back(Polygon{ circle.back(), circle.front(), center });
        for (size_t i = 1; i < size; ++i) {
            res.push_back(Polygon{ circle[i - 1], circle[i], center });
        }
    }

    float HPartCount(1), RPartCount(1);
    while (RPartSize * RPartCount < radius) {
        auto inner(circle);
        auto outer(circle);

        for (auto& i : inner)
            i.x() *= RPartCount, i.y() *= RPartCount;
        ++RPartCount;
        for (auto& i : outer)
            i.x() *= RPartCount, i.y() *= RPartCount;

        res.push_back(Polygon{ inner[size - 1], outer[size - 1], outer[0], inner[0] });
        for (size_t i = 1; i < size; ++i)
            res.push_back(Polygon{ inner[i - 1], outer[i - 1], outer[i], inner[i] });
    }
    std::vector<Polygon> partres(res);
    for (auto& i : partres) {
        for (auto& elem : i)
            elem.z() += height;
    }
    res.insert(res.begin(), partres.begin(), partres.end());

    //  боковая сторона
    for (auto& i : circle)
        i.x() *= RPartCount, i.y() *= RPartCount;

    Vector3f h(0, 0, height);
    res.push_back(Polygon{
        circle.front(),
        circle.front() + h,
        circle.back() + h,
        circle.back(),
    });
    for (size_t i = 1; i < circle.size(); ++i)
        res.push_back(Polygon{
            circle[i - 1],
            circle[i - 1] + h,
            circle[i] + h,
            circle[i],
        });

    return Figure(res);
}