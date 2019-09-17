#pragma once

#include <QWidget>

#include <QOpenGLWidget>
// #include <QtOpenGL>
// #include <QGLWidget>
// #include <GL/glu.h>

#include <algorithm>
#include <cmath>
// #include <functional>
#include <vector>

class OGLWidget : public QOpenGLWidget {
public:
    OGLWidget(QWidget* parent = 0);
    ~OGLWidget() =default;

    void set(double a, double b, double A, double B, double step);
    bool polar;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // void self_cursor(); // метод для рисования своего курсора
    // void keyPressEvent(QKeyEvent* ke); // Для перехвата нажатия клавиш на клавиатуре
    // void mouseMoveEvent(QMouseEvent* me); // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
    // void wheelEvent(QWheelEvent*) override;
    // void mousePressEvent(QMouseEvent* me); // Реагирует на нажатие кнопок мыши
    // void mouseReleaseEvent(QMouseEvent* me); // Метод реагирует на "отжатие" кнопки мыши
    // void singling_lb(); // Рисуем рамку выделенной области
    // void geese(); // Рисуем квадрат по которому кликать для получения очков

private:
    template <class Func, class Iter>
    std::vector<double> calculate(Func&& f, Iter first, Iter last);
    void Psinus();
    double scale;
    double a, b, A, B, step;
};
