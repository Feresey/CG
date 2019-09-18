#pragma once

#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>

#include <algorithm>
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
    void restore_scale()
    {
        scale = save_scale;
        update();
        scale_is_normal();
        scale_changed(scale);
    }
    void restore_position()
    {
        zero = normalize;
        angle = 0.0;
        update();
    }
    void set_x(int val)
    {
        zero.setX(val - normalize.x());
        update();
    }
    void set_y(int val)
    {
        zero.setY(val - normalize.y());
        update();
    }
    void set_angle(double val)
    {
        angle = val;
        update();
    }

signals:
    void scale_changed(double);
    void scale_is_small(QString = QString("Scale is too small, please restore it"));
    void scale_is_normal();
    void x_changed(int);
    void y_changed(int);
    void angle_changed(double);

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
    void Psinus();
    void findScale();
    double scale;
    double save_scale;
    std::vector<double> phi;
    std::vector<double> x, y;
    QPoint zero, prev_pos, normalize;
    bool mouse_tapped;
    Qt::MouseButton button_pressed;
    double angle = 0;

#ifdef GIRO
    bool bol = true;
    void inf()
    {
        sleep(1);
        timespec ts = { 0, 1000 }, tv;
        while (bol) {
            nanosleep(&ts, &tv);
            paintGL();
            update();
        }
    }

    std::future<void> launch;
#endif
};
