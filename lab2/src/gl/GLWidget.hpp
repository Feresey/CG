#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QOpenGLWidget>
#include <QVector2D>
#include <QVector3D>
#include <QWheelEvent>
#include <QWidget>

#include <array>
#include <cmath>
#include <vector>

class Polygon;

const float D2R = M_PIf32 / 180.0f;

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public slots:
    void restore();
    void norm();
    void set_scale(double);
    void redraw();
    void color(bool);
    void edges(bool);
    void base(bool);
    void project(int);
    void set_phi(double);
    void set_theta(double);


signals:
    void scale_changed(double);
    void scale_message(QString = { "Scale is too small, please restore it" });
    void phi_changed(double);
    void theta_changed(double);
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
    float findScale();
    void LoadMatrix();

    std::vector<Polygon> figures;
    std::vector<Polygon> changed_figures;
    std::vector<bool> display_figures;
    QVector3D inside;

    QPoint zero, prev_pos, normalize;
    Qt::MouseButton button_pressed;

    float scale,
        angle_phi,
        angle_theta;

    bool mouse_tapped,
        color_enabled,
        edges_enabled,
        base_enabled;
    int ignore_angle;

    int pr;
    unsigned int seed;
};

#endif
