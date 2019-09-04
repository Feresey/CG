#include <vector>

#include "GLWidget.hpp"
#include "Matrix.hpp"
#include "Polygon.hpp"

#include <QVector3D>
GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , approx(3)
    , mode(flat)
    , figure()
    , cyllinderHeight(3)
    , cyllinderRadius(1)
    , zero()
    , prev_pos()
    , normalize()
    , button_pressed(Qt::MouseButton::NoButton)
    , scale(100)
    , Ka(0.3f)
    , ia(0.7f)
    , Kd(0.8f)
    , il(1)
    , Ks(1)
    , K(0)
    , ip(6)
    , angle(0, 0, 0)
    , light(0, 0, 20)
    , moved_light()
    , lightColor(1, 0, 0)
    , objectColor(1, 1, 1)
    , color_enabled(true)
    , edges_enabled(true)
    , base_enabled(true)
    , is_move_light(false)
    , is_opengl(false)
    , draw_normales(false)
    , seed()
{
    rand_r(&seed);
    gen_figuries();
}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    auto_scale();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT); // чистим буфер изображения и буфер глубины
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
