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

    Matrix m = Ry(angle_theta) * Rx(angle_phi);

    // Move figure
    QPoint tmp = zero - normalize;
    tmp.setX(-tmp.x());
    m *= Sh(scale) * Move({ float(tmp.x()), float(tmp.y()), 0.0f });

    std::vector<Polygon> changed_figures(figures.size());
    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [m](const Polygon& p) { return m * p; });

    QVector3D inside;
    size_t total = 0;
    for (const auto& i : changed_figures)
        for (const auto& j : i) {
            ++total;
            inside += j;
        }
    inside /= static_cast<float>(total);

    display_figures.clear();
    Matrix view = Matrix{ changed_figures, inside };
    view = Matrix{ { 0, 0, 1, 0 }, 1, 4 } * view;
    for (size_t i = 0; i < changed_figures.size(); ++i)
        if (view[i] > 0)
            display_figures.push_back(changed_figures[i]);

    update();
}

float GLWidget::findScale()
{
    return 100;
}

void GLWidget::Draw()
{
    for (auto poly : display_figures) {
        if (edges_enabled) {
            glColor3d(1, 1, 1);
            glBegin(GL_LINE_LOOP);
            for (auto point : poly)
                glVertex2d(point[0], point[1]);
            glEnd();
        }
        if (color_enabled) {
            glColor3fv(poly.getColor());
            glBegin(GL_POLYGON);
            for (auto point : poly)
                glVertex2d(point[0], point[1]);
            glEnd();
        }
    }

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

    if (base_enabled) {
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
