// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "GLWidget.hpp"

#include <vector>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , figures()
    , changed_figures()
    // , display_figures()
    , zero()
    , prev_pos()
    , normalize()
    , mouse_tapped(false)
    , button_pressed()
    , m(4, 4)
    , scale(100)
    , angle_phi(0.0)
    , angle_theta(180.0)
    , color_enabled(true)
    , edges_enabled(true)
    , seed(new unsigned int())
{
    rand_r(seed.get());
    std::vector<QVector3D> base;
    int number = 5;
    for (size_t i = 0; i < number; ++i) {
        float tmp = static_cast<float>(i) * 2.0f / number * M_PIf32;
        base.push_back({ cosf(tmp), sinf(tmp), 0 });
    }
    QVector3D top = { 0, 0, 3 }, 
			  bottom = { 0, 0, 0 };
    figures.push_back({ base.front(), base.back(), bottom });

    figures.push_back({ base.front(), base.back(), top });
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
    restore();
    redraw();
    LoadMatrix();
    z_buffer.assign(width() * height(), std::numeric_limits<int>::min());
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
    z_buffer.assign(width() * height(), std::numeric_limits<int>::min());

    Draw();
    // for (size_t i = 0; i < changed_figures.size(); ++i) {
    //     if (color_enabled) {
    //         glBegin(GL_POLYGON);
    //         glColor3d(changed_figures[i].r(), changed_figures[i].g(), changed_figures[i].b());
    //         for (auto j : display_figures[i])
    //             glVertex2d(j.x() * scale, j.y() * scale);
    //         glEnd();
    //     }
    //     if (edges_enabled) {
    //         glColor3d(1, 1, 1);

    //         glBegin(GL_LINE_LOOP);
    //         for (auto j : display_figures[i])
    //             glVertex2d(j.x() * scale, j.y() * scale);
    //         glEnd();
    //     }
    // }

    glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    z_buffer.assign(width() * height(), std::numeric_limits<int>::min());

    restore();
}
