#pragma once

#include <GL/glu.h>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

class OGLWidget : public QOpenGLWidget {
public:
    OGLWidget(QWidget* parent = 0);
    ~OGLWidget();

    void set(double a, double b, double A, double B, double step);
    void setSeed(double s);
    void resize(double val);
    bool polar;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    int geese_size; // Сторона квадрата
    int point; // набранные очки
    int gdx, gdy; // Координаты квадрата
    int cax, cay, cbx, cby;
    bool singling; // Для выделение области, если true то рисуем прямоугольник по координатам cax, cay, cbx, cby
    // void self_cursor(); // метод для рисования своего курсора
    // void keyPressEvent(QKeyEvent* ke); // Для перехвата нажатия клавиш на клавиатуре
    // void mouseMoveEvent(QMouseEvent* me); // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
    // void mousePressEvent(QMouseEvent* me); // Реагирует на нажатие кнопок мыши
    // void mouseReleaseEvent(QMouseEvent* me); // Метод реагирует на "отжатие" кнопки мыши
    // void singling_lb(); // Рисуем рамку выделенной области
    // void geese(); // Рисуем квадрат по которому кликать для получения очков

private:
    template <class Func, class Iter>
    std::vector<double> calculate(Func&& f, Iter first, Iter last);
    void Psinus();
    double scale;
    double seed=0.25;
    double a, b, A, B, step;
};
