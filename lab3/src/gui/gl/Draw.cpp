#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

#include <algorithm>
#include <functional>
#include <future>
#include <iostream>

void GLWidget::gen_figuries()
{
    auto f = GenCylinder(cyllinderHeight, cyllinderRadius, approx);
    figure = f;
    Apply();
}

void GLWidget::Apply()
{
    QPoint tmp = zero - normalize;
    Matrix m(Rx(angle.x()) * Ry(angle.y()) * Rz(angle.z()));
    Matrix move(Move({ -float(tmp.x()), float(tmp.y()), 0.0f }));
    if (is_move_light)
        moved_light = m * move * light;
    m *= Sh(scale) * move;
    figure.LoadMatrix(m);
    repaint();
}

void GLWidget::Draw()
{
    if (base_enabled)
        draw_base();
    for (const auto& tr : figure) {
        if (draw_normales) {
            glColor3d(1, 1, 1);
            glBegin(GL_LINE_STRIP);
            Vector3f center(tr.getCenter());
            glVertex2f(center.x(), center.y());
            center += tr.getNormal() * 50;
            glVertex2f(center.x(), center.y());
            glEnd();
        }
        if (edges_enabled) {
            glColor3d(1, 1, 1);
            glBegin(GL_LINE_LOOP);
            glVertex2f(tr[0].x(), tr[0].y());
            glVertex2f(tr[1].x(), tr[1].y());
            glVertex2f(tr[2].x(), tr[2].y());
            glEnd();
        }
        if (color_enabled) {
            if (is_opengl) {
                const auto& normal = tr.getNormal();
                glBegin(GL_POLYGON);
                glColor3fv(Guro(tr[0], normal).v);
                glVertex2f(tr[0].x(), tr[0].y());
                glColor3fv(Guro(tr[1], normal).v);
                glVertex2f(tr[1].x(), tr[1].y());
                glColor3fv(Guro(tr[2], normal).v);
                glVertex2f(tr[2].x(), tr[2].y());
                glEnd();
            } else {
                glBegin(GL_POINTS);
                // glColor3f(1, 0.5, 0);
                triangle(tr);
                glEnd();
            }
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
    glVertex2f(display_base[0].x(), display_base[0].y());
    glVertex2f(center.x(), center.y());
    glEnd();
    // y
    glColor3d(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(display_base[1].x(), display_base[1].y());
    glVertex2f(center.x(), center.y());
    glEnd();
    // z
    glColor3d(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glVertex2f(display_base[2].x(), display_base[2].y());
    glVertex2f(center.x(), center.y());
    glEnd();
}
