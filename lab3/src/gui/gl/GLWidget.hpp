#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include "config.hpp"

#include <QDebug>
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

typedef enum {
    flat,
    guro,

    total
} Shading;

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public slots:
    void set_scale(double);
    void color(bool);
    void edges(bool);
    void base(bool);
    void move_light(bool);
    void opengl_enabled(bool);
    void normales_enabled(bool);
    void initial_state();
    void auto_scale();
    void change_colors();
    void set_angle(Vector3f, char);
    void set_approx(int);
    void set_mode(int);

    void set_light(Vector3f, char);
    void set_Ka(double);
    void set_ia(double);
    void set_Kd(double);
    void set_il(double);
    void set_Ks(double);

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
    void gen_figuries();
    void Draw();
    void Apply();
    // Vector3f Phong(const Vector3f& point, const Vector3f& normal) const;
    Vector3f Guro(const Vector3f& point, const Vector3f& normal) const;
    // void AppendMatrix();
    void triangle(const Polygon& tr);
    void draw_base();

    int approx;
    Shading mode;

    Figure figure;
    float cyllinderHeight,cyllinderRadius;

    QPoint zero, prev_pos, normalize;
    Qt::MouseButton button_pressed;

    float scale,
    // восприимчивость к рассеянному
        Ka,
        // мощность рассеянного
        ia,
        // восриимчивость к диффузному
        Kd,
        // мощность источника света
        il,
        // блик
        Ks,
        // хуйня какая-то
        K,
        // коэфф. блика
        ip;
    Vector3f angle, light, moved_light, lightColor, objectColor;

    bool
        color_enabled,
        edges_enabled,
        base_enabled,
        is_move_light,
        is_opengl,
        draw_normales;

    unsigned int seed;
};

#endif
