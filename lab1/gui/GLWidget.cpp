// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <cmath>
#include <vector>

#include "GLWidget.hpp"

OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , polar(false)
    , scale(1)
    , a(1)
    , b(2)
    , A(-720)
    , B(720)
    , step(0.005)
{
}

void OGLWidget::initializeGL()
{
    // qglClearColor(Qt::black);
    glClearColor(0, 0, 0, 1);
}

void OGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(-width() / 2, width() / 2, -height() / 2, height() / 2, 1, 0); // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);
    glShadeModel(GL_SMOOTH);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
    glEnable(GL_POLYGON_SMOOTH);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);

    Psinus();
}

void OGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
}

void OGLWidget::set(double aa, double bb, double AA, double BB, double sstep)
{
    a = aa;
    b = bb;
    A = AA;
    B = BB;
    step = sstep;
}

void OGLWidget::Psinus()
{
    std::vector<double> phi;
    double last = M_PI * B / 180;
    for (double i = M_PI * A / 180; i < last; i += step)
        phi.push_back(i);
    size_t size = phi.size();

    std::vector<double> y(size), x(size);
    std::transform(phi.begin(), phi.end(), x.begin(), [&](double var) { return a * var + b * sin(var); });
    std::transform(phi.begin(), phi.end(), y.begin(), [&](double var) { return a - b * cos(var); });

    if (polar) {
        std::transform(x.begin(), x.end(), y.begin(), x.begin(), [](double _x, double _y) { return sqrt(_x * _x + _y * _y); });
        std::transform(x.begin(), x.end(), phi.begin(), y.begin(), [](double _ro, double _phi) { return _ro * sin(_phi); });
        std::transform(x.begin(), x.end(), phi.begin(), x.begin(), [](double _ro, double _phi) { return _ro * cos(_phi); });
    }
    auto _abs = [](double a, double b) { return abs(a) < abs(b); };

    double xmax = abs(*std::max_element(x.begin(), x.end(), _abs));
    double ymax = abs(*std::max_element(y.begin(), y.end(), _abs));

    scale = std::min(width(), height()) * 0.9 / (std::max(xmax, ymax) * 2);

    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i + 1 < size; i += 1)
        glVertex2d(scale * x[i], scale * y[i]);
    glEnd();
}
