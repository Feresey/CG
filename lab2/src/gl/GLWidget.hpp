#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QOpenGLWidget>
#include <QVector3D>
#include <QWheelEvent>
#include <QWidget>

#include <algorithm>
#include <array>
#include <vector>

#include "Matrix.hpp"

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public slots:
    void restore();
    void set_scale(double);

signals:
    void scale_changed(double);
    void scale_message(QString = { "Scale is too small, please restore it" });

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
    double findScale();

    std::vector<std::vector<QVector3D>> figures;

    QPoint zero, prev_pos, normalize;
    bool mouse_tapped;
    Qt::MouseButton button_pressed;

    Matrix m;

    double scale;

    double angle_phi, angle_theta;
    double Z_x, Z_y, Z_z;
};

#endif
