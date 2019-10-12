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
    Matrix m = Sh(scale) * Move(tmp);
    QVector3D eye = m * QVector3D(0, 0, 10);
    m = Rx(angle_phi) * Ry(angle_theta) * m;
    std::vector<Polygon> changed_figures(figures.size());

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [&](const Polygon& p) { return m * p; });

    QVector3D changed_inside = m * inside;
    display_figures.clear();
    Matrix view = Matrix{ changed_figures, changed_inside };
    view = Matrix{ { eye.x(), eye.y(), eye.z(), 0 }, 1, 4 } * view;
    for (size_t i = 0; i < changed_figures.size(); ++i)
        if (view[i] > 0)
            display_figures.push_back(changed_figures[i]);

    // std::vector<std::vector<int>> layer(changed_figures.size());
    // for (size_t i = 0; i < changed_figures.size(); ++i) {
    //     for (size_t j = 0; j < changed_figures.size(); ++j)
    //         layer[i].push_back(changed_figures[i].cmp(changed_figures[j]));
    //     layer[i][i] = 0;
    // }

    // for (auto& i : changed_figures)
    //     for (auto& j : changed_figures) {
    //         int res = i.cmp(j);
    //         if (res == 1)
    //             std::swap(i, j);
    //     }

    //         for (auto i : changed_figures) {
    //             for (auto j : changed_figures) {
    //                 int tmp = i.cmp(j);
    //                 std::cout << (tmp < 0 ? "" : " ") << tmp << ' ';
    //             }
    //             std::cout << std::endl;
    //         }
    // std::cout << "\n\n";

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
            // glVertex3d(point[0],point[1],point[2]);
            glVertex2d(point[0], point[1]);
        glEnd();
    }
}
