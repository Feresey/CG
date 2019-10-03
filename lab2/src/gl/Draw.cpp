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
    update();
}

void GLWidget::LoadMatrix()
{
    m = Matrix(4, 4);
    // m[2 + 4 * 2] = 0;
    m = Sh(0, 0, 0) * Rx(angle_phi) * Ry(angle_theta);

    Matrix _tmp = m * Matrix({ 5, 5, 5, 1 }, 4, 1);
    QVector3D Z = { _tmp[0], _tmp[1], _tmp[2] };
    std::sort(figures.begin(), figures.end(),
        [&](const Polygon& l, const Polygon& r) { return l.max_distance(Z) > r.max_distance(Z); });

    for (size_t i = 0; i < figures.size(); ++i)
        for (size_t j = 0; j < figures[i].size(); ++j) {
            QVector3D tmp = m * figures[i][j];
            display_figures[i][j] = QVector2D{
                static_cast<float>(tmp.x() * scale),
                static_cast<float>(tmp.y() * scale)
            };
        }
    // std::transform(figures[i].begin(), figures[i].end(), display_figures[i].begin(),
    //     [&](const QVector3D& point) {
    //         QVector3D tmp = m * point;
    //         return QVector2D{ static_cast<float>(tmp.x() * scale),
    //             static_cast<float>(tmp.y() * scale) };
    //     });

    update();
}

double GLWidget::findScale()
{
    return 100;
}
