#include <vector>

#include "GLWidget.hpp"
#include "Polygon.hpp"

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , figures()
    , changed_figures()
    , zero()
    , prev_pos()
    , normalize()
    , mouse_tapped(false)
    , button_pressed()
    , scale(100)
    , angle_phi(0.0)
    , angle_theta(180.0)
    , color_enabled(true)
    , edges_enabled(true)
    , seed(new unsigned int())
{
    rand_r(seed.get());
    std::vector<QVector3D> base;
    size_t number = 5;
    for (size_t i = 0; i < number; ++i) {
        float tmp = float(i) * 2.0f / float(number) * M_PIf32;
        base.push_back({ cosf(tmp), sinf(tmp), 0 });
    }
    QVector3D top = { 0, 0, 3 }, bottom = { 0, 0, 0 };
    figures.push_back({ base.front(), base.back(), bottom });
    figures.push_back({ base.front(), base.back(), top });
    // int i = 2;
    for (size_t i = 1; i < base.size(); ++i) {
        figures.push_back({ base[i - 1], base[i], top });
        figures.push_back({ base[i - 1], base[i], bottom });
    }
    changed_figures.resize(figures.size());
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    restore();
    redraw();
    // z_buffer.assign(width() * height(), std::numeric_limits<int>::min());
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(-width() / 2, width() / 2,
        -height() / 2, height() / 2,
        -1000, 1000); // подготавливаем плоскости для матрицы
    // z_buffer.assign(width() * height(), std::numeric_limits<int>::min());

    Draw();

    glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);


    // z_buffer.assign(width() * height(), std::numeric_limits<int>::min());

    restore();
}
