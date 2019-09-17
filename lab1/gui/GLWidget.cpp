// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <cmath>
#include <vector>

#include "GLWidget.hpp"

OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , polar(false)
    , geese_size(30)
    , point(0)
    , gdx()
    , gdy()
    , cax()
    , cay()
    , cbx()
    , cby()
    , singling(false)
    , scale(1)
    , a(1)
    , b(2)
    , A(-720)
    , B(720)
    , step(0.001)
{
}

void OGLWidget::wheelEvent(QWheelEvent* event)
{
    int delta = event->delta();
    auto rescale = (delta > 0 ? 0.9 : 1.1);
    delta = abs(delta);
    while (delta--) {
        // std::cout << "here" << std::endl;
        // resizeGL(width(), height());
        // glScaled(rescale,rescale,1);
        // updateGL();
    }
}

void OGLWidget::initializeGL()
{
    // qglClearColor(Qt::black);
        glClearColor(0, 0, 0, 1);
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
        std::transform(x.begin(), x.end(), y.begin(), x.begin(), [&](double _x, double _y) { return sqrt(_x * _x + _y * _y); });
        std::transform(x.begin(), x.end(), phi.begin(), y.begin(), [&](double _ro, double _phi) { return _ro * sin(_phi); });
        std::transform(x.begin(), x.end(), phi.begin(), x.begin(), [&](double _ro, double _phi) { return _ro * cos(_phi); });
    }
    auto xmax = std::minmax_element(x.begin(), x.end());
    double xx = abs(*xmax.first) + abs(*xmax.second);
    auto ymax = std::minmax_element(x.begin(), x.end());
    double yy = abs(*ymax.first) + abs(*ymax.second);
    scale = width() * 0.5 / std::max(xx,yy);
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i + 1 < size; i += 1)
        glVertex2d(scale * y[i] + width() / 2, -scale * x[i] + width() / 2);
    glEnd();
}

void OGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(0, width(), height(), 0, 1, 0); // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Psinus();

    // glBegin(GL_POLYGON);
    // glColor3f(1, 0, 0); // Цвет курсора
    // // Координаты курсора
    // glVertex2f(cax, cay);
    // glVertex2f(cax + 20, cay + 20);
    // glVertex2f(cax + 8, cay + 20);
    // glVertex2f(cax, cay + 30);
    // glEnd();
}
// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// glMatrixMode(GL_PROJECTION);
//     glLoadIdentity(); // загружаем матрицу

// glOrtho(0, width(), height(), 0, 1, 0); // подготавливаем плоскости для матрицы
// glEnable(GL_BLEND);
// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// Psinus();

// glPushMatrix();
// glBegin(GL_LINES);
// glVertex2d(0, -width());
// glVertex2d(0, width());
// glVertex2d(-height() / 2, 0);
// glVertex2d(height() / 2, 0);
// // glVertex2d(0, 0);
// // glVertex2d(1, 1);
// glEnd();
// glPopMatrix();

// glPushMatrix();
// glColor3d(1, 1, 1);
// glBegin(GL_LINES);
// for (int i = -(width() / 2); i <= (width() / 2); i += 1) {
//     /*glVertex2d(0, 0);
//     glVertex2d(1, 1);*/
//     glVertex2d(scale * i, scale * (-height() / 2));
//     glVertex2d(scale * i, scale * (height() / 2));
// }
// for (int i = -(height() / 2); i <= (height() / 2); i += 1) {
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
// swapBuffers();
// }
void OGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(0.0f, width(), height(), 0.0f, 0.0f, 1.0f);
    // glOrtho(-(w / 2), (w / 2), -(h / 2), (h / 2), -5, 5);

    glViewport(0, 0, w, h);
}
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(90, static_cast<GLdouble>(w) / h, 0.01, 100.0);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//     gluLookAt(0, 0, -5,
//         0, 0, 0,
//         10, 0, -1);
//     glFlush();
// }

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
