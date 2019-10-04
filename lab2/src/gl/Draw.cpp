#include "GLWidget.hpp"

Matrix Rx(double _phi)
{
    float phi = float(_phi);
    return Matrix(
        {
            cosf(phi), 0, -sinf(phi), 0,
            0, 1, 0, 0,
            sinf(phi), 0, cosf(phi), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Ry(double _theta)
{
    float theta = float(_theta);
    return Matrix(
        {
            1, 0, 0, 0,
            0, cosf(theta), sinf(theta), 0,
            0, -sinf(theta), cosf(theta), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Sh(double _x, double _y, double _z)
{
    float x = static_cast<float>(_x), y = static_cast<float>(_y), z = static_cast<float>(_z);
    return Matrix({
                      1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      x, y, z, 1 //
                  },
        4, 4);
}

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
    m = Sh(0, 0, 0) * Rx(angle_phi) * Ry(angle_theta);

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [&](const Polygon& p) { return m * p; });
    std::sort(changed_figures.begin(), changed_figures.end(),
        [&](const Polygon& l, const Polygon& r) { return l.max_distance() > r.max_distance(); });

    Matrix project_z(4, 4);
    project_z[2 + 4 * 2] = 0;

    for (size_t i = 0; i < changed_figures.size(); ++i)
        for (size_t j = 0; j < changed_figures[i].size(); ++j)
            display_figures[i][j] = project_z.projection(changed_figures[i][j]);

    update();
}

double GLWidget::findScale()
{
    return 100;
}
