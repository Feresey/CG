#include <QOpenGLContext>


#include <algorithm>
#include <functional>
#include <future>
#include <iostream>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

void GLWidget::gen_figuries()
{
    float _height = 3;
    float radius = 1;
    float step = 360.f * D2R / static_cast<float>(approx);
    float curr = 0.f;
    std::vector<Vector3f> bottom;
    bottom.reserve(approx);
    for (int i = 0; i < approx; ++i) {
        bottom.push_back(Vector3f{ radius * cosf(curr), radius * sinf(curr), -1.5f });
        curr += step;
    }
    std::vector<Vector3f> top(bottom.size());
    std::transform(bottom.begin(), bottom.end(), top.begin(),
        [_height](Vector3f v) { v.z()+=_height; return v; });
    std::vector<Polygon> f;
    f.reserve(approx + 3UL);
    f.push_back(bottom);
    f.push_back(top);
    f.push_back(Polygon{ bottom.front(), bottom.back(), top.back(), top.front() });
    for (size_t i = 1; i < bottom.size(); ++i)
        f.push_back(Polygon{ bottom[i - 1], bottom[i], top[i], top[i - 1] });
    figure.SetFigures(f);
}

void GLWidget::Apply()
{
    QPoint tmp = zero - normalize;
    Matrix m = Rx(angle.x()) * Ry(angle.y()) * Rz(angle.z())
        * Sh(scale) * Move({ -float(tmp.x()), float(tmp.y()), 0.0f });
    figure.LoadMatrix(m);
    update();
}

#define MAX_PROCS 1

void GLWidget::Draw()
{
    std::vector<std::vector<Polygon>> todo(MAX_PROCS);
    uint8_t curr = 0;
    if (base_enabled) {
        draw_base();
    }
    for (const auto& i : figure) {
        for (const auto& tr : i.to_triangles()) {
            if (edges_enabled) {
                glColor3d(1, 1, 1);
                glBegin(GL_LINE_LOOP);
                glVertex2d(tr[0].x(), tr[0].y());
                glVertex2d(tr[1].x(), tr[1].y());
                glVertex2d(tr[2].x(), tr[2].y());
                glEnd();
            }
            // glColor3d(1, 0, 0);
            // glBegin(GL_POINTS);
            if (color_enabled) {
                // triangle(tr);
                todo[curr].push_back(tr);
                curr = ++curr % MAX_PROCS;
            }
            // glEnd();
        }
    }
    if (color_enabled) {
        std::vector<std::future<void>> run(MAX_PROCS);
        for (size_t i = 0; i < MAX_PROCS; ++i) {
            run[i] = std::async(std::launch::async,
                [&](const std::vector<Polygon>& src) {
                    for (const auto& j : src)
                        triangle(j);
                },
                todo[i]);
        }
        is_point.resize(points.size());
        for (size_t i = 0; i < MAX_PROCS; ++i)
            run[i].wait();
        glBegin(GL_POINTS);
        for (size_t i = 0; i < points.size(); ++i)
            if (is_point[i]) {
                glColor3fv(points[i].v);
                glVertex2i(i / _width, i % _width);
            }
        glEnd();
    }
}

std::mutex draw;

void GLWidget::triangle(const Polygon& tr)
{
    auto v2p = [](const Vector3f& src) -> QPoint { return { int(floorf(src.x() + 0.5f)), int(floorf(src.y() + 0.5f)) }; };
    QPoint v1 = v2p(tr[0]),
           v2 = v2p(tr[1]),
           v3 = v2p(tr[2]);
    if (v3.y() < v2.y())
        std::swap(v2, v3);
    if (v3.y() < v1.y())
        std::swap(v1, v3);
    if (v2.y() < v1.y())
        std::swap(v2, v1);
    const int total_height = v3.y() - v1.y();

    int bottom_y = std::max(v1.y(), 0),
        top_y = std::min(v3.y(), int(_height));
    if (bottom_y > _height || top_y < 0)
        return;
    auto norm = tr.to_plane();
    if (abs(norm[2]) < EPS)
        return;
    for (int y = v1.y(); y <= v3.y(); ++y) {
        bool top = y >= v2.y() || v1.y() == v2.y();
        int segment_height = (top ? v3.y() - v2.y() : v2.y() - v1.y());
        float alpha = static_cast<float>((y - v1.y())) / float(total_height);
        float beta = static_cast<float>((y - (top ? v2.y() : v1.y()))) / float(segment_height);
        QPoint A = v1 + (v3 - v1) * alpha;
        QPoint B = (top ? v2 : v1) + (top ? v3 - v2 : v2 - v1) * beta;
        if (A.x() > B.x())
            std::swap(A, B);
        int bottom_x = std::max(A.x(), 0),
            top_x = std::min(B.x(), int(_width));
        if (bottom_x > _width || top_x < 0)
            continue;
        draw.lock();
        for (int j = A.x(); j <= B.x(); ++j) {
            size_t pos = j * _width + y;
            if (j < 0 || y < 0 || pos >= points.size())
                continue;
            points[pos] = Vector3f{ 1, 0, 0 };
            is_point[pos] = true;
        }
        draw.unlock();
    }
    QOpenGLContext q;

    // qDebug("triangle");
}

void GLWidget::draw_base()
{
    std::vector<Vector3f> display_base({ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
    float offset = 40.0;
    Vector3f center = {
        float(_width) - offset * 2.0f,
        offset * 2.0f,
        0.0f
    };
    Matrix m = Ry(angle.y()) * Rx(angle.x()) * Rz(angle.z()) * Sh(offset) * Move(center);
    std::transform(display_base.begin(), display_base.end(), display_base.begin(),
        [m](const Vector3f& v) { return m * v; });

    // x
    glColor3d(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2d(display_base[0].x(), display_base[0].y());
    glVertex2d(center.x(), center.y());
    glEnd();
    // y
    glColor3d(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2d(display_base[1].x(), display_base[1].y());
    glVertex2d(center.x(), center.y());
    glEnd();
    // z
    glColor3d(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glVertex2d(display_base[2].x(), display_base[2].y());
    glVertex2d(center.x(), center.y());
    glEnd();
}
