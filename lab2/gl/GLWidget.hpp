#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>

#include <algorithm>
#include <vector>

#include "Polygon.hpp"

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public slots:
    void restore();
    void set_angle(double);
    void set_scale(double);

signals:
    void scale_changed(double);
    void scale_message(QString = { "Scale is too small, please restore it" });
    void x_changed(int);
    void y_changed(int);
    void angle_changed(double);
    void point_pos(QPointF);

public:
    GLWidget(QWidget* parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void wheelEvent(QWheelEvent*) override;
    void mouseMoveEvent(QMouseEvent* me) override; // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
    void mousePressEvent(QMouseEvent* me) override; // Реагирует на нажатие кнопок мыши
    void mouseReleaseEvent(QMouseEvent* me) override; // Метод реагирует на "отжатие" кнопки мыши

private:
    void Draw();
    double findScale();

    QVector<Polygon> figures;

    QPoint zero, prev_pos, normalize;
    bool mouse_tapped;
    Qt::MouseButton button_pressed;
    double scale, save_scale, angle;
};

#endif
