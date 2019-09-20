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
#ifdef GIRO
    , launch(std::async(std::bind(&GLWidget::inf, this)))
#endif
{
}

GLWidget::~GLWidget()
{
#ifdef GIRO
    bol = false;
#endif
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    calculate();
    normalize = QPoint(width() / 2, -height() / 2);
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
#ifdef GIRO
    std::ifstream in("/sys/devices/platform/lis3lv02d/position");
    in.get();
    std::string a;
    std::getline(in, a, ',');
    glRotated(-double(atoi(a.c_str()) / 10) / 1.2222222, 0, 0, 1);
#endif

    glRotated(angle, 0, 0, 1);

    Psinus();

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

    findScale();
    normalize = QPoint(width() / 2, -height() / 2);
}

void GLWidget::wheelEvent(QWheelEvent* we)
{
    int dl = we->delta();
    scale *= 1 + 0.001 * dl;

    if (scale < 0.0000001)
        emit scale_is_small();
    else
        scale_is_normal();

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

void GLWidget::findScale()
{
    auto _abs = [](double l, double r) { return abs(l) < abs(r); };

    double xmax = abs(*std::max_element(x.begin(), x.end(), _abs));
    double ymax = abs(*std::max_element(y.begin(), y.end(), _abs));

    save_scale = std::min(width(), height()) * 0.9 / (std::max(xmax, ymax) * 2);
    restore();
}

void GLWidget::Psinus()
{
    // QPoint tmp = zero - normalize;
    // tmp.setX(-tmp.x());

    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i + 1 < phi.size(); i += 1)
        glVertex2d(scale * x[i], scale * y[i]);
    glEnd();
}

void GLWidget::calculate(double a, double b, double A, double B, int points)
{
    phi.resize(0);
    double first = M_PI * A / 180,
           last = M_PI * B / 180;
    double delta = (last - first) / points;
    double curr = first;

    for (int i = 0; i <= points; ++i, curr += delta)
        phi.push_back(curr);
    phi.push_back(last);

    size_t size = phi.size();

    y.resize(size);
    x.resize(size);
    auto th1 = std::async(
        [&]() { return std::transform(phi.begin(), phi.end(), x.begin(),
                    [&](double var) { return a * var + b * sin(var); }); });
    auto th2 = std::async(
        [&]() { return std::transform(phi.begin(), phi.end(), y.begin(),
                    [&](double var) { return a - b * cos(var); }); });

    th1.wait();
    th2.wait();

    std::transform(x.begin(), x.end(), y.begin(), x.begin(),
        [](double _x, double _y) { return sqrt(_x * _x + _y * _y); });

    std::transform(x.begin(), x.end(), phi.begin(), y.begin(),
        [](double _ro, double _phi) { return _ro * sin(_phi); });
    std::transform(x.begin(), x.end(), phi.begin(), x.begin(),
        [](double _ro, double _phi) { return _ro * cos(_phi); });

    findScale();
}
