#include "GLWidget.hpp"
#include "Polygon.hpp"
#include "Vector3I.hpp"

#include <iostream>
#include <iomanip>

const float EPS = 1e-4f;

Matrix Rx(float phi)
{
    return Matrix(
        {
            cosf(phi), 0, -sinf(phi), 0,
            0, 1, 0, 0,
            sinf(phi), 0, cosf(phi), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Ry(float theta)
{
    return Matrix(
        {
            1, 0, 0, 0,
            0, cosf(theta), sinf(theta), 0,
            0, -sinf(theta), cosf(theta), 0,
            0, 0, 0, 1 //
        },
        4, 4);
}

Matrix Sh(float x, float y, float z)
{
    return Matrix({
                      x, 0, 0, 0,
                      0, y, 0, 0,
                      0, 0, z, 0,
                      0, 0, 0, 1 //
                  },
        4, 4);
}

Matrix Move(QPointF delta)
{
    return Matrix({
                      1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      float(delta.x()), float(delta.y()), 0, 1 //
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
    QPointF tmp = zero - normalize;
    tmp.setX(-tmp.x());
    m = Move(tmp) * Sh(scale, scale, scale) * Rx(angle_phi) * Ry(angle_theta);

    std::transform(figures.begin(), figures.end(), changed_figures.begin(),
        [&](const Polygon& p) { return m * p; });
	
	// for(size_t i = 0; i < changed_figures.size(); ++i)
    for (auto& i : changed_figures)
        for (auto& j : changed_figures) {
            int res = i.cmp(j);
            if (res == 1)
                std::swap(i, j);
        }
	// std::cout.precision(2);
	// std::cout.width(2);
	for(auto i: changed_figures){
		for(auto j: changed_figures){
			int tmp = i.cmp(j);
			std::cout << (tmp < 0? "" : " ") << tmp << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n";
    // changed_figures.sort();
    // for(size_t i = 0; i < changed_figures.size(); ++i)
    // std::stable_sort(changed_figures.begin(), changed_figures.end());

    update();
}

double GLWidget::findScale()
{
    return 100;
}

void GLWidget::Draw()
{

    for (auto poly : changed_figures) {
        glColor3fv(poly.getColor());

        //*
        glBegin(GL_POLYGON);
        for (auto point : poly)
            // glVertex3d(point[0],point[1],point[2]);
            glVertex2d(point[0], point[1]);
        glEnd();
        /*/
            // std::cout << poly << std::endl;

            if (poly[0].y() > poly[1].y())
                std::swap(poly[0], poly[1]);
            if (poly[0].y() > poly[2].y())
                std::swap(poly[0], poly[2]);
            if (poly[1].y() > poly[2].y())
                std::swap(poly[1], poly[2]);
            int total_height = static_cast<int>(poly[2].y() - poly[0].y());
            if (total_height == 0) continue;
for (int i = 0; i < total_height; ++i) {
                bool second_half = (float(i) > poly[1].y() - poly[0].y())
                    || (poly[1].y() == poly[0].y());
                int segment_height = static_cast<int>(second_half ? poly[2].y() - poly[1].y()
                                                                  : poly[1].y() - poly[0].y());
if (segment_height == 0 ) continue;
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
                        continue;
                    if (abs(P.y()) > height() / 2)
                        continue;
                    int idx = P.x() + width() / 2 + (P.y() + height() / 2) * height();
                    // std::cout << P << std::endl;
                    // std::cout << "w:" << idx / width() << " h:" << idx % width() << std::endl;
                    if (z_buffer[idx] < P.z()) {
                        z_buffer[idx] = P.z();
                        glVertex2i(P.x(), P.y());
                        // image.set(P.x, P.z(), color);
                    }
                }
                glEnd();
            }
            //*/
    }
}
