#include <iostream>

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
    QPointF tmp = zero - normalize;
    tmp.setX(-tmp.x());
    Matrix m = Sh(scale) * Move(tmp);
    QVector3D eye = m * QVector3D(0, 0, 100);
    m = Rx(angle_phi) * Ry(angle_theta) * m;
    std::vector<Polygon> changed_figures(figures.size());

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [&](const Polygon& p) { return m * p; });

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
    view = Matrix{ { eye.x(), eye.y(), eye.z(), 0 }, 1, 4 } * view;
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
        glColor3fv(poly.getColor());

        glBegin(GL_POLYGON);
        for (auto point : poly)
            glVertex2d(point[0], point[1]);
        glEnd();
    }
}
