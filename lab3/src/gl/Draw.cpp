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

    // orthogonal projections
    float local_phi, local_theta;
    switch (pr) {
    case 1:
        local_phi = 0;
        local_theta = 0;
        break;
    case 2:
        local_phi = 0;
        local_theta = -90 * D2R;
        break;
    case 3:
        local_phi = -90 * D2R;
        local_theta = local_phi;
        break;
    case 4:
        local_phi = 35 * D2R;
        local_theta = -45 * D2R;
        break;
    default:
        local_phi = local_theta = 0;
        break;
    }
    QPoint tmp = zero - normalize;
    tmp.setX(-tmp.x());

    Matrix m = Ry(pr == 0 ? angle_theta : local_theta) * Rx(pr == 0 ? angle_phi : local_phi)
        * Sh(scale, scale, scale)
        * Move(pr == 0 || pr == 4 ? QVector3D{ float(tmp.x()), float(tmp.y()), 0.0f } : QVector3D{ 0, 0, 0 });

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [m](const Polygon& p) { return m * p; });

    Matrix view = Matrix{ { 0, 0, ((pr != 0 && cosf(angle_phi) > 0) ? 1.0f : -1.0f), 0 }, 1, 4 }
        * Matrix{ changed_figures, m * inside };
    for (size_t i = 0; i < changed_figures.size(); ++i)
        display_figures[i] = view[i] > 0;

    if (pr != 0 && pr != 4) {
        m = Sh(1, 1, 0)
            * Ry(angle_theta) * Rx(angle_phi)
            * Move({ float(tmp.x()), float(tmp.y()), 0.0f });

        std::for_each(changed_figures.begin(), changed_figures.end(),
            [m](Polygon& p) { p = m * p; });
    }

    update();
}

float GLWidget::findScale()
{
    const QVector3D& one = changed_figures[0][0];
    float mx_x = one.x(), mx_y = one.y(), mn_x = one.x(), mn_y = one.y();
    for (const auto& i : changed_figures) {
        auto max = i.max(), min = i.min();
        if (max.x() > mx_x)
            mx_x = max.x();
        if (max.y() > mx_y)
            mx_y = max.y();
        if (min.x() < mn_x)
            mn_x = min.x();
        if (min.y() < mn_y)
            mn_y = min.y();
    }
    std::vector<float> anus = { abs(mn_x), abs(mn_y), abs(mx_x), abs(mx_y) };
    std::sort(anus.begin(), anus.end());
    return float(std::min(width(), height())) * 0.45f / (anus.back() / scale);
}

void triangle(Polygon tr)
{
    std::sort(tr.begin(), tr.end(),
        [](const QVector3D& l, const QVector3D& r) { return l.y() < r.y(); });
    auto v2p = [](const QVector3D& src) -> QPoint { return { int(src.x()), int(src.y()) }; };
    const QPoint v1 = v2p(tr[0]),
                 v2 = v2p(tr[1]),
                 v3 = v2p(tr[2]);
    if (v1.y() == v2.y() && v1.y() == v3.y())
        return;
    int total_height = v3.y() - v1.y();
    // for (int y = v1.y(); y <= v2.y(); y++) {
    //     int segment_height = v2.y() - v1.y() + 1;
    //     float alpha = static_cast<float>((y - v1.y())) / total_height;
    //     float beta = static_cast<float>((y - v1.y())) / segment_height; // be careful with divisions by zero
    //     QPoint A = v1 + (v3 - v1) * alpha;
    //     QPoint B = v1 + (v2 - v1) * beta;
    //     if (A.x() > B.x())
    //         std::swap(A, B);
    //     for (int j = A.x(); j <= B.x(); j++)
    //         glVertex2i(j, y);
    // }
    // for (int y = v2.y(); y <= v3.y(); y++) {
    //     int segment_height = v3.y() - v2.y() + 1;
    //     float alpha = static_cast<float>((y - v1.y())) / total_height;
    //     float beta = static_cast<float>((y - v2.y())) / segment_height; // be careful with divisions by zero
    //     QPoint A = v1 + (v3 - v1) * alpha;
    //     QPoint B = v2 + (v3 - v2) * beta;
    //     if (A.x() > B.x())
    //         std::swap(A, B);
    //     for (int j = A.x(); j <= B.x(); j++)
    //         glVertex2i(j, y);
    // }

    for (int y = v1.y(); y <= v3.y(); ++y) {
        bool top = y > v2.y();
        int segment_height = (top ? v3.y() - v2.y() : v2.y() - v1.y()) + 1;
        float alpha = static_cast<float>((y - v1.y())) / total_height;
        float beta = static_cast<float>((y - (top ? v2.y() : v1.y()))) / segment_height; // be careful with divisions by zero
        QPoint A = v1 + (v3 - v1) * alpha;
        QPoint B = (top ? v2 : v1) + (top ? v3 - v2 : v2 - v1) * beta;
        if (A.x() > B.x())
            std::swap(A, B);
        for (int j = A.x(); j <= B.x(); ++j)
            glVertex2i(j, y);
    }
}

void GLWidget::Draw()
{
    if (base_enabled) {
        std::vector<QVector3D> display_base({ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
        float offset = 40.0;
        QVector3D center = {
            float(width()) / 2.0f - offset * 2.0f,
            float(-height()) / 2.0f + offset * 2.0f,
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

    for (size_t i = 0; i < display_figures.size(); ++i) {
        if (!display_figures[i])
            continue;
        if (color_enabled) {
            glBegin(GL_POINTS);
            glColor3fv(changed_figures[i].getColor());
            triangle(changed_figures[i]);
            glEnd();
        }
        // if (color_enabled) {
        //     glColor3fv(changed_figures[i].getColor());
        //     glBegin(GL_POLYGON);
        //     for (auto point : changed_figures[i])
        //         glVertex2d(point[0], point[1]);
        //     glEnd();
        // }
    }
}
