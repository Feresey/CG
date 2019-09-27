// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "GLWidget.hpp"

#include <cmath>
#include <vector>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , scale(1)
    , save_scale(1)
    , phi()
    , x()
    , y()
    , zero(0, 0)
    , prev_pos(0, 0)
    , normalize(0, 0)
    , mouse_tapped(false)
    , button_pressed()
    , angle(0)
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
    QPoint tmp = zero - normalize;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(-width() / 2 + tmp.x(), width() / 2 + tmp.x(),
        -height() / 2 - tmp.y(), height() / 2 - tmp.y(),
        1, 0); // подготавливаем плоскости для матрицы
    glRotated(angle, 0, 0, 1);

    Draw();

    glBegin(GL_LINES);
    glVertex2d(-2 * width() + zero.x(), 0);
    glVertex2d(2 * width() + zero.x(), 0);
    glVertex2d(0, -2 * height() - zero.y());
    glVertex2d(0, 2 * height() - zero.y());
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

    if (scale < 0.0000001)
        scale_message();
    else
        scale_message("");

    update();
    scale_changed(scale);
}

void GLWidget::mouseMoveEvent(QMouseEvent* me)
{
    if (mouse_tapped) {
        QPoint tmp = zero - normalize;

        switch (button_pressed) {
        case Qt::MouseButton::LeftButton:
            zero += prev_pos - me->pos();
            x_changed(tmp.x());
            y_changed(tmp.y());
            break;
        case Qt::MouseButton::RightButton:
            angle += (prev_pos - me->pos()).x() * 0.2;
            angle_changed(angle);
            break;
        default:
            break;
        }

        prev_pos = me->pos();
        update();
    }
    QPoint tmp = me->pos() + zero;
    tmp.setX(tmp.x() - width());
    tmp.setY(-tmp.y());
    point_pos({ 1. * tmp.x() / scale, 1. * tmp.y() / scale });
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
    // auto _abs = [](double l, double r) { return abs(l) < abs(r); };

    // double xmax = abs(*std::max_element(x.begin(), x.end(), _abs));
    // double ymax = abs(*std::max_element(y.begin(), y.end(), _abs));

    // return std::min(width(), height()) * 0.9 / (std::max(xmax, ymax) * 2);
    return 1;
}

void GLWidget::restore()
{
    scale = save_scale = findScale();
    update();
    scale_message("");
    scale_changed(scale);

    zero = normalize = { width() / 2, -height() / 2 };
    x_changed(0);
    y_changed(0);

    angle = 0.0;
    angle_changed(0.0);
    update();
}

void GLWidget::set_angle(double val)
{
    angle = val;
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
