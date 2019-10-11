#include <iostream>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

void GLWidget::redraw()
{
    for (auto& i : figures)
        i.setColor(QVector3D{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) });
    LoadMatrix();
}

void GLWidget::LoadMatrix()
{
    QPointF tmp = zero - normalize;
    tmp.setX(-tmp.x());
    Matrix m = Move(tmp) * Sh(scale, scale, scale) * Rx(angle_phi) * Ry(angle_theta);

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [&](const Polygon& p) { return m * p; });

    for (auto& i : changed_figures)
        for (auto& j : changed_figures) {
            int res = i.cmp(j);
            if (res == 1)
                std::swap(i, j);
        }

    for (auto i : changed_figures) {
        for (auto j : changed_figures) {
            int tmp = i.cmp(j);
            std::cout << (tmp < 0 ? "" : " ") << tmp << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";

    update();
}

float GLWidget::findScale()
{
    return 100;
}

void GLWidget::Draw()
{

    for (auto poly : changed_figures) {
        glColor3fv(poly.getColor());

        glBegin(GL_POLYGON);
        for (auto point : poly)
            // glVertex3d(point[0],point[1],point[2]);
            glVertex2d(point[0], point[1]);
        glEnd();
    }
}
