// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <cmath>
#include <vector>

#include "oglwidget.h"
#include "config.h"

OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    // glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHTING);
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(width() / 2), (width() / 2), -(height() / 2), (height() / 2), -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glScaled(0.25, 0.25, 1);
}

template <class Func, class Iter>
std::vector<double> OGLWidget::calculate(Func&& f, Iter first, Iter last)
{
    std::vector<double> res;
    for (Iter it = first; it != last; ++it)
        res.push_back(f(*it));
    return res;
}

void OGLWidget::Psinus()
{
    std::vector<double> phi;
    for (double i = M_PI * A / 180; i < M_PI * B / 180; i += step)
        phi.push_back(i);
    std::vector<double> y = calculate([&](double var) { return a * var + b * sin(var); }, phi.begin(), phi.end()),
                        x = calculate([&](double var) { return a - b * cos(var); }, phi.begin(), phi.end());
#ifdef POLAR
    std::vector<double> ro(phi.size());
    std::transform(x.begin(), x.end(), y.begin(), ro.begin(), [&](double _x, double _y) { return sqrt(_x * _x + _y * _y); });
    std::transform(ro.begin(), ro.end(), phi.begin(), x.begin(), [&](double _ro, double _phi) { return _ro * cos(_phi); });
    std::transform(ro.begin(), ro.end(), phi.begin(), y.begin(), [&](double _ro, double _phi) { return _ro * sin(_phi); });
#endif
    size_t size = phi.size();

    glBegin(GL_LINE_STRIP);

    for (size_t i = 0; i + 1 < size; i += 1)
        glVertex2d(seed * scale * x[i], seed * scale * y[i]);
    glEnd();
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Psinus();

    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2d(0, -width());
    glVertex2d(0, width());
    glVertex2d(-height() / 2, 0);
    glVertex2d(height() / 2, 0);
    // glVertex2d(0, 0);
    // glVertex2d(1, 1);
    glEnd();
    glPopMatrix();

    // glPushMatrix();
    // glColor3d(1, 1, 1);
    // glBegin(GL_LINES);
    // for (double i = -(width() / 2); i <= (width() / 2); i += 20) {
    //     glVertex2d(0, 0);
    //     glVertex2d(1, 1);
    //     glVertex2d(scale * i, scale * (-height() / 2));
    //     glVertex2d(scale * i, scale * (height() / 2));
    // }
    // for (double i = -(height() / 2); i <= (height() / 2); i += 20) {
    //     glVertex2d(scale * -(width() / 2), scale * i);
    //     glVertex2d(scale * (width() / 2), scale * i);
    // }
    // glEnd();
    // glPopMatrix();

    // glBegin(GL_TRIANGLES);
    // glColor3f(1.0, 0.0, 0.0);
    // glVertex3f(-0.5, -0.5, 0);
    // glColor3f(0.0, 1.0, 0.0);
    // glVertex3f(0.5, -0.5, 0);
    // glColor3f(0.0, 0.0, 1.0);
    // glVertex3f(0.0, 0.5, 0);
    // glEnd();
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)w / h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -5,
        0, 0, 0,
        10, 0, -1);
}

void OGLWidget::set(double aa, double bb, double AA, double BB, double sstep)
{
    a = aa;
    b = bb;
    A = AA;
    B = BB;
    step = sstep;
}

void OGLWidget::resize(double _scale)
{
    scale = _scale;
    // paintGL();
    // glScaled(scale, scale, 1);
}

void OGLWidget::setSeed(double s)
{
    seed += s;
}
