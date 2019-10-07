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
                      x, 0, 0, 0,
                      0, y, 0, 0,
                      0, 0, z, 0,
                      0, 0, 0, 1 //
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
// #include <iostream>

void GLWidget::LoadMatrix()
{
    m = Sh(scale, scale, scale) * Rx(angle_phi) * Ry(angle_theta);

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [&](const Polygon& p) { return m * p; });

    // std::stable_sort(changed_figures.begin(), changed_figures.end());

    // std::stable_sort(changed_figures.begin(), changed_figures.end(),
    //     [&](const Polygon& l, const Polygon& r) { return l.max() < r.max(); });
    // std::stable_sort(changed_figures.begin(), changed_figures.end(),
    //     [&](const Polygon& l, const Polygon& r) { return l.min() < r.min(); });

    // std::cout << "first:\t" << changed_figures.front() << "\nlast:\t" << changed_figures.back() << std::endl;
    // Matrix project_z(4, 4);
    // project_z[2 + 4 * 2] = 0;
    // display_figures.resize(figures.size());
    // for (size_t i = 0; i < changed_figures.size(); ++i) {
    //     display_figures[i].resize(changed_figures[i].size());
    //     for (size_t j = 0; j < changed_figures[i].size(); ++j)
    //         display_figures[i][j] = project_z.projection(changed_figures[i][j]);
    // }

    update();
}

double GLWidget::findScale()
{
    return 100;
}

#include "Vector3I.hpp"

#include <iostream>

void GLWidget::Draw()
{
    for (auto poly : changed_figures) {
        glColor3fv(poly.getColor());
        // std::cout << poly << std::endl;
        if (poly[0].y() > poly[1].y())
            std::swap(poly[0], poly[1]);
        if (poly[0].y() > poly[2].y())
            std::swap(poly[0], poly[2]);
        if (poly[1].y() > poly[2].y())
            std::swap(poly[1], poly[2]);
        int total_height = static_cast<int>(poly[2].y() - poly[0].y());
        for (int i = 0; i < total_height; ++i) {
            bool second_half = (float(i) > poly[1].y() - poly[0].y())
                || (poly[1].y() == poly[0].y());
            int segment_height = static_cast<int>(second_half ? poly[2].y() - poly[1].y()
                                                              : poly[1].y() - poly[0].y());
            float alpha = float(i) / float(total_height);
            float beta = float((float(i) - (second_half ? poly[1].y() - poly[0].y() : 0)) / float(segment_height));
            // be careful: with above conditions no division by zero here
            Vector3I A = poly[0] + (poly[2] - poly[0]) * alpha;
            Vector3I B = second_half ? poly[1] + (poly[2] - poly[1]) * beta
                                     : poly[0] + (poly[1] - poly[0]) * beta;
            if (A.x() > B.x())
                std::swap(A, B);

            glBegin(GL_POINTS);
            for (int j = A.x(); j <= B.x(); j++) {
                float phi = B.x() == A.x() ? 1.0f : float(j - A.x()) / float(B.x() - A.x());
                Vector3I P = A + (B - A) * phi;
                if (abs(P.x()) > width() / 2)
                    break;
                if (abs(P.y()) > height() / 2)
                    break;
                int idx = P.x() + width() / 2 + (P.y() + height() / 2) * height();
                // std::cout << P << std::endl;
                // std::cout << "w:" << idx / width() << " h:" << idx % width() << std::endl;
                if (z_buffer[idx] < P.z()) {
                    z_buffer[idx] = P.z();
                    glVertex2d(P.x(), P.y());
                    // image.set(P.x, P.z(), color);
                }
            }
            glEnd();
        }
    }
}