#include <algorithm>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

void GLWidget::redraw()
{
    const float mx = static_cast<float>(RAND_MAX);
    for (auto& i : figures)
        i.setColor(QVector3D{
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx });
    LoadMatrix();
}

void GLWidget::LoadMatrix()
{
    QPoint tmp = zero - normalize;
    tmp.setX(-tmp.x());
    Matrix m = Ry(angle_theta) * Rx(angle_phi)*Sh(scale) * Move({ float(tmp.x()), float(tmp.y()), 0.0f });

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [m](const Polygon& p) { return m * p; });

    Matrix view = Matrix{ { 0, 0, 1, 0 }, 1, 4 } * Matrix{ changed_figures, m * inside };
    for (size_t i = 0; i < changed_figures.size(); ++i)
        display_figures[i] = view[i] > 0;

    update();
}

float GLWidget::findScale()
{
    return 100;
}

void GLWidget::Draw()
{
    for (size_t i = 0; i < display_figures.size(); ++i) {
        if (!display_figures[i])
            continue;
        if (edges_enabled) {
            glColor3d(1, 1, 1);
            glBegin(GL_LINE_LOOP);
            for (auto point : changed_figures[i])
                glVertex2d(point[0], point[1]);
            glEnd();
        }
        if (color_enabled) {
            glColor3fv(changed_figures[i].getColor());
            glBegin(GL_POLYGON);
            for (auto point : changed_figures[i])
                glVertex2d(point[0], point[1]);
            glEnd();
        }
    }

    if (base_enabled) {
        std::vector<QVector3D> display_base({ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
        float offset = 40.0;
        QVector3D center = {
            static_cast<float>(width() / 2 - offset * 2),
            static_cast<float>(-height() / 2 + offset * 2),
            0.0f
        };
        Matrix m = Ry(angle_theta) * Rx(angle_phi) * Sh(offset) * Move(center);
        std::transform(display_base.begin(), display_base.end(), display_base.begin(),
            [m](const QVector3D& v) { return m * v; });

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
}
