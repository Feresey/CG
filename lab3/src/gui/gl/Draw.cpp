#include <algorithm>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

#include <iostream>

void GLWidget::LoadMatrix()
{
    QPoint tmp = zero - normalize;
    Matrix m = Rx(angle.x()) * Ry(angle.y()) * Rz(angle.z())
        * Sh(scale) * Move({ -float(tmp.x()), float(tmp.y()), 0.0f });
    figure.LoadMatrix(m);
    figure.Sort({ 0, 0, 1 });
    update();
}


void GLWidget::Draw()
{
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
            if (color_enabled) {
                glColor3fv(i.getColor());
                glBegin(GL_POINTS);
                triangle(tr);
                glEnd();
            }
        }
    }
}

void GLWidget::triangle(Polygon tr)
{
    std::sort(tr.begin(), tr.end(),
        [](const Vector3f& l, const Vector3f& r) { return l.y() < r.y(); });
    auto v2p = [](const Vector3f& src) -> QPoint { return { int(floorf(src.x() + 0.5f)), int(floorf(src.y() + 0.5f)) }; };
    const QPoint v1 = v2p(tr[0]),
                 v2 = v2p(tr[1]),
                 v3 = v2p(tr[2]);
    if (v1.y() == v2.y() && v1.y() == v3.y())
        return;
    const int total_height = v3.y() - v1.y();

    int bottom_y = std::max(v1.y(), 0),
        top_y = std::min(v3.y(), height());
    if (bottom_y > height() || top_y < 0)
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
            top_x = std::min(B.x(), width());
        if (bottom_x > width() || top_x < 0)
            continue;
        for (int j = A.x(); j <= B.x(); ++j) {
            glVertex2i(j, y);
        }
    }
}

void GLWidget::draw_base()
{
    std::vector<Vector3f> display_base({ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
    float offset = 40.0;
    Vector3f center = {
        float(width()) - offset * 2.0f,
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
