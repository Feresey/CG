#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QOpenGLWidget>
#include <QVector2D>
#include <QWheelEvent>
#include <QWidget>

#include <array>
#include <cmath>
#include <vector>

#include "Figure.hpp"
#include "Vector.hpp"

class Polygon;

const float D2R = M_PIf32 / 180.0f;
const float EPS = 1e-8f;

enum {
    axonometric,
    project_xy,
    project_xz,
    project_yz,
    izometric
};

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public slots:
    void restore();
    void restore_all();
    void set_scale(double);
    void redraw();
    void color(bool);
    void edges(bool);
    void base(bool);
    void project(int);
    void set_x(double);
    void set_y(double);
    void set_z(double);

signals:
    void scale_changed(double);
    void scale_message(QString = { "Scale is too small, please restore it" });
    void x_changed(double);
    void y_changed(double);
    void z_changed(double);
    void set_project(int);

public:
    GLWidget(QWidget* parent = 0);
    ~GLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void wheelEvent(QWheelEvent*) override;
    void mouseMoveEvent(QMouseEvent* me) override;
    void mousePressEvent(QMouseEvent* me) override;
    void mouseReleaseEvent(QMouseEvent* me) override;

private:
    void Draw();
    void LoadMatrix();
    void triangle(Polygon tr);

    Figure figure;

    QPoint zero, prev_pos, normalize;
    Qt::MouseButton button_pressed;

    float
        scale,
        angle_x,
        angle_y,
        angle_z;

    bool
        color_enabled,
        edges_enabled,
        base_enabled;

    int pr;
    unsigned int seed;
};

#endif
