#include <vector>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , approx(3)
    , figure()
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
    // qDebug().setVerbosity(QDebug::MaximumVerbosity);
    qDebug("Enter constructor");
    rand_r(&seed);
    gen_figuries();
    qDebug("Leave constructor");
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
    qDebug("Prepare to Draw");
    Draw();

    glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    qDebug("Resize");
    auto_scale();
}
