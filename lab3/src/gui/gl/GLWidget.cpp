#include <vector>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , zero()
    , prev_pos()
    , normalize()
    , button_pressed(Qt::MouseButton::NoButton)
    , scale(100)
    , angle({ 0, 0, 0 })
    , color_enabled(true)
    , edges_enabled(true)
    , base_enabled(true)
    , seed()
{
    rand_r(&seed);
    std::vector<Polygon> figures;
    /*
    figures = {
        { { 1, -1, -1 }, { 1, 1, -1 }, { 1, 1, 1 }, { 1, -1, 1 } }, // front
        { { -1, -1, -1 }, { -1, 1, -1 }, { -1, 1, 1 }, { -1, -1, 1 } }, // back
        { { 1, 1, -1 }, { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 } }, //right
        { { 1, -1, -1 }, { -1, -1, -1 }, { -1, -1, 1 }, { 1, -1, 1 } }, //left
        { { 1, -1, 1 }, { 1, 1, 1 }, { -1, 1, 1 }, { -1, -1, 1 } }, // top
        { { 1, -1, -1 }, { 1, 1, -1 }, { -1, 1, -1 }, { -1, -1, -1 } } //bottom
    };

    // figures.push_back();
    /*/

    std::vector<Vector3f> bottom_points;
    size_t number = 5;
    for (size_t i = 0; i < number; ++i) {
        float tmp = float(i) * 2.0f / float(number) * M_PIf32;
        bottom_points.push_back({ cosf(tmp), sinf(tmp), 0 });
    }

    Vector3f top = { 0, 0, 2 }, bottom = { 0, 0, 0 };
    figures.push_back({ bottom_points.front(), bottom_points.back(), top });
    figures.push_back({ bottom_points.front(), bottom_points.back(), bottom });

    for (size_t i = 1; i < bottom_points.size(); ++i) {
        figures.push_back({ bottom_points[i], bottom_points[i - 1], top });
        figures.push_back({ bottom_points[i], bottom_points[i - 1], bottom });
    }
    //*/

    figure = Figure(figures);
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    auto_scale();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity();
    glOrtho(0, width(),
        0, height(),
        -1000, 1000); // подготавливаем плоскости для матрицы

    Draw();

    glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    auto_scale();
}
