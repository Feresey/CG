#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>

#include <algorithm>
#include <cmath>
#include <vector>

#include "config.h"

#include <future>
#ifdef GIRO
#include <fstream>
#include <unistd.h>
#endif

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public slots:
    void restore()
    {
        scale = save_scale;
        update();
        scale_is_normal();
        scale_changed(scale);

        zero = normalize;
        x_changed(0);
        y_changed(0);

        _angle = angle = 0.0;
        angle_changed(0.0);
        update();
    }

    void set_angle(double val)
    {
        angle = val;
        _angle = angle * M_PI / 180;
        update();
    }

    void set_scale(double var)
    {
        scale = var;
        if (scale < 0.0000001)
            scale_is_small();
        else
            scale_is_normal();
        update();
    }

signals:
    void scale_changed(double);
    void scale_is_small(QString = QString("Scale is too small, please restore it"));
    void scale_is_normal();
    void x_changed(int);
    void y_changed(int);
    void angle_changed(double);
    void point_pos(QPointF);

public:
    GLWidget(QWidget* parent = 0);
    ~GLWidget();

    void calculate(double a = 1., double b = 2.,
        double A = -720., double B = 720.,
        int points = 5000);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // void self_cursor(); // метод для рисования своего курсора
    // void keyPressEvent(QKeyEvent* ke); // Для перехвата нажатия клавиш на клавиатуре

    void wheelEvent(QWheelEvent*) override;
    void mouseMoveEvent(QMouseEvent* me) override; // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
    void mousePressEvent(QMouseEvent* me) override; // Реагирует на нажатие кнопок мыши
    void mouseReleaseEvent(QMouseEvent* me) override; // Метод реагирует на "отжатие" кнопки мыши

    // void singling_lb(); // Рисуем рамку выделенной области
    // void geese(); // Рисуем квадрат по которому кликать для получения очков

private:
    void findScale();
    double scale;
    double save_scale;
    std::vector<double> phi;
    std::vector<double> x, y;
    QPoint zero, prev_pos, normalize;
    bool mouse_tapped;
    Qt::MouseButton button_pressed;
    double angle, _angle;

#ifdef GIRO
    bool bol = true;
    void inf()
    {
        sleep(1);
        timespec ts = { 0, 10000 }, tv;
        while (bol) {
            nanosleep(&ts, &tv);
            paintGL();
            update();
        }
    }

    std::future<void> launch;
#endif
};

#endif
