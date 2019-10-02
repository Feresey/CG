// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "GLWidget.hpp"

#include <cmath>
#include <vector>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , figures(
          {
              { { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 0, 0 } }, // bottom
              { { 0, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 }, { 1, 0, 1 } }, // top
              { { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 1, 0, 1 } }, // front
              { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 } }, // back
              { { 0, 0, 0 }, { 1, 0, 0 }, { 1, 0, 1 }, { 0, 0, 1 } }, // left
              { { 0, 1, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 0, 1, 1 } }, // right
          })
    , zero()
    , prev_pos()
    , normalize()
    , mouse_tapped(false)
    , button_pressed()
    , m(4, 4)
    , scale(1)
    , angle_phi()
    , angle_theta()
    , Z_x()
    , Z_y()
    , Z_z()
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    restore();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(-width() / 2, width() / 2,
        -height() / 2, height() / 2,
        1, 0); // подготавливаем плоскости для матрицы

    for (auto i : figures) {
        glBegin(GL_LINE_LOOP);
        for (auto j : i) {

            // glVertex2d(j)
        }
        glEnd();
    }

    glBegin(GL_LINES);
    glVertex2d(-2 * width(), 0);
    glVertex2d(2 * width(), 0);
    glVertex2d(0, -2 * height());
    glVertex2d(0, 2 * height());
    glEnd();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    restore();
}

void GLWidget::wheelEvent(QWheelEvent* we)
{
    int dl = we->delta();
    scale *= 1 + 0.001 * dl;

    set_scale(scale);
    scale_changed(scale);
}

void GLWidget::mouseMoveEvent(QMouseEvent* me)
{
    if (mouse_tapped) {
        zero += prev_pos - me->pos();

        switch (button_pressed) {
        case Qt::MouseButton::LeftButton:
            break;
        case Qt::MouseButton::RightButton:
            break;
        case Qt::MouseButton::MiddleButton:
            break;
        default:
            break;
        }

        prev_pos = me->pos();
        update();
    }
}

void GLWidget::mousePressEvent(QMouseEvent* me)
{
    mouse_tapped = true;
    button_pressed = me->button();
    prev_pos = me->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* me)
{
    mouse_tapped = false;
    prev_pos = me->pos();
}

double GLWidget::findScale()
{
    return 1;
}

void GLWidget::restore()
{
    scale = findScale();
    update();
    scale_message("");
    scale_changed(scale);

    zero = normalize = { width() / 2, -height() / 2 };
    update();
}

void GLWidget::set_scale(double val)
{
    scale = val;
    if (scale < 0.0000001)
        scale_message();
    else
        scale_message("");
    update();
}
