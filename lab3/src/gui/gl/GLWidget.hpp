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
#include "config.hpp"

class Polygon;

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
    void set_scale(double);
    void color(bool);
    void edges(bool);
    void base(bool);
    void initial_state();
    void auto_scale();
    void change_colors();
    void set_angle(Vector3f, char);
    void set_approx(int);

signals:
    void scale_changed(double);
    void scale_message(QString = { "Scale is too small, please restore it" });
    void angle_changed(Vector3f);

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
    void draw_base();

    Figure figure;

    QPoint zero, prev_pos, normalize;
    Qt::MouseButton button_pressed;

    float scale;
    Vector3f angle;

    bool
        color_enabled,
        edges_enabled,
        base_enabled;

    unsigned int seed;
};

#endif
