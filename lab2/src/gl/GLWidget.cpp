// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "GLWidget.hpp"

#include <vector>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , figures({
          { { 1, -1, -1 }, { 1, 1, -1 }, { -1, 1, -1 }, { -1, -1, -1 } }, //bottom
          { { 1, -1, 1 }, { 1, 1, 1 }, { -1, 1, 1 }, { -1, -1, 1 } }, // top
          { { 1, 1, -1 }, { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 } }, //right
          { { 1, -1, -1 }, { -1, -1, -1 }, { -1, -1, 1 }, { 1, -1, 1 } }, //left
          { { 1, -1, -1 }, { 1, 1, -1 }, { 1, 1, 1 }, { 1, -1, 1 } }, // front
          { { -1, -1, -1 }, { -1, 1, -1 }, { -1, 1, 1 }, { -1, -1, 1 } } // back
          //   { { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 0, 0 } }, // bottom
          //   { { 0, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 }, { 1, 0, 1 } }, // top
          //   { { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 1, 0, 1 } }, // front
          //   { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 } }, // back
          //   { { 0, 0, 0 }, { 1, 0, 0 }, { 1, 0, 1 }, { 0, 0, 1 } }, // left
          //   { { 0, 1, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 0, 1, 1 } } // right
      })
    , display_figures({
          { {}, {}, {}, {} },
          { {}, {}, {}, {} },
          { {}, {}, {}, {} },
          { {}, {}, {}, {} },
          { {}, {}, {}, {} },
          { {}, {}, {}, {} } //
      })
    , zero()
    , prev_pos()
    , normalize()
    , mouse_tapped(false)
    , button_pressed()
    , m(4, 4)
    , scale(100)
    , angle_phi(30.0)
    , angle_theta(45.0)
    , Z_x()
    , Z_y()
    , Z_z()
    , seed(new unsigned int())
{
    rand_r(seed.get());
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    restore();
    redraw();
    LoadMatrix();
}
// #include <iostream>
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(-width() / 2, width() / 2,
        -height() / 2, height() / 2,
        1, 0); // подготавливаем плоскости для матрицы

    for (size_t i = 0; i < figures.size(); ++i) {
        glBegin(GL_POLYGON);
        glColor3d(figures[i].r(), figures[i].g(), figures[i].b());
        for (auto j : display_figures[i]) {
            glVertex2d(j.x(), j.y());
        }
        glEnd();
    }

    glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    restore();
}
