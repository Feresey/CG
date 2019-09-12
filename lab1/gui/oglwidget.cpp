#include "oglwidget.h"
#include <cmath>
#include <vector>

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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-(width() / 2), (width() / 2), -(height() / 2), (height() / 2), -5, 5);
    // glMatrixMode(GL_MODELVIEW);
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
    size_t size = phi.size();

    glBegin(GL_LINE_STRIP);

    for (size_t i = 0; i + 1 < size; i += 1) {
        glVertex2d(0.05 * scale * x[i], 0.05 * scale * y[i]);
        // glVertex2d( * x[i + 1],  * y[i + 1]);
    }
    glEnd();
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Psinus();

glPushMatrix();
glBegin(GL_LINES);
    glVertex2d(0,-width());
    glVertex2d(0,width());
    glVertex2d(-height() / 2,0);
    glVertex2d(height() / 2,0);
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
    gluPerspective(45, (float)w / h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 10, 0, 0);
}

void OGLWidget::set(double aa, double bb, double AA, double BB, double sstep)
{
    a = aa;
    b = bb;
    A = AA;
    B = BB;
    b = bb;
    step = sstep;
}

void OGLWidget::resize(double _scale)
{
    scale = _scale;
    // paintGL();
    glScaled(scale, scale, 1);
}
