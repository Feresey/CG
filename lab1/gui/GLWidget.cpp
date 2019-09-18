// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "GLWidget.hpp"
#include <cmath>
#include <vector>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , polar(false)
    , scale(1)
    , a(1)
    , b(2)
    , A(-720)
    , B(720)
    , step(0.005)
    , phi()
    , x()
    , y() 
    , x0()
    , y0()
#ifdef GIRO
    , launch(std::async(std::bind(&GLWidget::inf, this)))
#endif
{
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    calculate();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(-width() / 2, width() / 2, -height() / 2, height() / 2, 1, 0); // подготавливаем плоскости для матрицы
    // gluPerspective(45.0f, (float)width() / (float)height(),0.01,100);
    // gluLookAt(5,5,-5,0,0,0,10,0,-1);
#ifdef GIRO
    std::ifstream in("/sys/devices/platform/lis3lv02d/position");
    in.get();
    std::string a;
    std::getline(in, a, ',');
    glRotated(-double(atoi(a.c_str())) / 12, 0, 0, 1);
#endif

    Psinus();

    glBegin(GL_LINES);
    glVertex2d(-width(), 0);
    glVertex2d(width(), 0);
    glVertex2d(0, -height());
    glVertex2d(0, height());
    glEnd();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    auto _abs = [](double a, double b) { return abs(a) < abs(b); };

    double xmax = abs(*std::max_element(x.begin(), x.end(), _abs));
    double ymax = abs(*std::max_element(y.begin(), y.end(), _abs));

    scale = std::min(width(), height()) * 0.9 / (std::max(xmax, ymax) * 2);
}

void GLWidget::set(double aa, double bb, double AA, double BB, double sstep)
{
    a = aa;
    b = bb;
    A = AA;
    B = BB;
    step = sstep;
    calculate();
}

void GLWidget::coord(int a)
{
    polar = a;
    update();
}

void GLWidget::calculate()
{
    double last = M_PI * B / 180;
    phi.resize(0);
    phi.push_back(M_PI * A / 180);

    for (double i = M_PI * A / 180; i < last; i += step)
        phi.push_back(i);
    size_t size = phi.size();

    y.resize(size);
    x.resize(size);
    std::transform(phi.begin(), phi.end(), x.begin(), [&](double var) { return a * var + b * sin(var); });
    std::transform(phi.begin(), phi.end(), y.begin(), [&](double var) { return a - b * cos(var); });

    // if (polar) {
    std::transform(x.begin(), x.end(), y.begin(), x.begin(), [](double _x, double _y) { return sqrt(_x * _x + _y * _y); });
    std::transform(x.begin(), x.end(), phi.begin(), y.begin(), [](double _ro, double _phi) { return _ro * sin(_phi); });
    std::transform(x.begin(), x.end(), phi.begin(), x.begin(), [](double _ro, double _phi) { return _ro * cos(_phi); });
    // }
}

void GLWidget::Psinus()
{
    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i + 1 < phi.size(); i += 1)
        glVertex2d(scale * x[i] + x0, scale * y[i] + y0);
    glEnd();
}