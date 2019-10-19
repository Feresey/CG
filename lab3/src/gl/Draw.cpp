#include <algorithm>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

void GLWidget::redraw()
{
    const float mx = static_cast<float>(RAND_MAX);
    for (auto& i : figures)
        i.setColor(
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx,
            static_cast<float>(rand()) / mx);
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

    Matrix m = Ry(pr == 0 ? angle_theta : local_theta) * Rx(pr == 0 ? angle_phi : local_phi); // rotate

    std::transform(figures.begin(), figures.end(), changed_figures.begin(), // apply changes
        [m](const Polygon& p) { return m * p; });

    Matrix view = Matrix{ { 0, 0, ((pr != 0 && cosf(angle_phi) > 0) ? 1.0f : -1.0f), 0 }, 1, 4 } // point of view
        * Matrix{ changed_figures, m * inside }; // matrix of normals
    for (size_t i = 0; i < changed_figures.size(); ++i)
        display_figures[i] = view[i] > 0;

    m = Sh(1);
    if (pr != 0 && pr != 4) {
        m = Sh(1, 1, 0) // drop z
            * Ry(angle_theta) * Rx(angle_phi); // rotate
    }
    QPoint tmp = zero - normalize;
    m *= Sh(scale) * Move({ -float(tmp.x()), float(tmp.y()), 0.0f });
    std::for_each(changed_figures.begin(), changed_figures.end(),
        [m](Polygon& p) { p = m * p; }); // apply changes

    update();
}

float GLWidget::findScale()
{
    const Vector3f& one = changed_figures[0][0];
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
    std::vector<float> anus = { abs(mn_x - normalize.x()), abs(mn_y + normalize.y()), abs(mx_x - normalize.x()), abs(mx_y + normalize.y()) };
    std::sort(anus.begin(), anus.end());
    // return float(std::min(width(), height())) * 0.45f / anus.back();
    return 100;
}

void GLWidget::Draw()
{
    if (base_enabled) {
        std::vector<Vector3f> display_base({ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
        float offset = 40.0;
        Vector3f center = {
            float(width()) - offset * 2.0f,
            offset * 2.0f,
            0.0f
        };
        Matrix m = Ry(angle_theta) * Rx(angle_phi) * Sh(offset) * Move(center);
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
    glBegin(GL_POINTS);
    for (size_t i = 0; i < display_figures.size(); ++i) {
        if (!display_figures[i])
            continue;
        glColor3fv(changed_figures[i].getColor());
        triangle(changed_figures[i]);
    }
    glEnd();
}

void GLWidget::triangle(Polygon tr)
{
    std::sort(tr.begin(), tr.end(),
        [](const Vector3f& l, const Vector3f& r) { return l.y() < r.y(); });
    auto v2p = [](const Vector3f& src) -> QPoint { return { int(src.x()), int(src.y()) }; };
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
        float alpha = static_cast<float>((y - v1.y())) / total_height;
        float beta = static_cast<float>((y - (top ? v2.y() : v1.y()))) / segment_height;
        QPoint A = v1 + (v3 - v1) * alpha;
        QPoint B = (top ? v2 : v1) + (top ? v3 - v2 : v2 - v1) * beta;
        if (A.x() > B.x())
            std::swap(A, B);
        int bottom_x = std::max(A.x(), 0),
            top_x = std::min(B.x(), width());
        if (bottom_x > width() || top_x < 0)
            continue;
        for (int j = A.x(); j <= B.x(); ++j) {
            // int pos = norm[4]
            // z_buffer[]
            glVertex2i(j, y);
        }
    }
}