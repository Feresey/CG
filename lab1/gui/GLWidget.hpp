#pragma once

#include <QOpenGLWidget>
#include <QWidget>

#include <algorithm>
#include <vector>

#include "config.h"

#ifdef GIRO
#include <fstream>
#include <future>
#include <unistd.h>
#endif

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public slots:
    void coord(int a);

public:
    GLWidget(QWidget* parent = 0);
    ~GLWidget()
    {
#ifdef GIRO
        bol = false;
#endif
    };

    void set(double a, double b, double A, double B, double step);
    bool polar;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // void self_cursor(); // метод для рисования своего курсора
    // void keyPressEvent(QKeyEvent* ke); // Для перехвата нажатия клавиш на клавиатуре

    // void wheelEvent(QWheelEvent*) override;
    // void mouseMoveEvent(QMouseEvent* me) override; // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
    // void mousePressEvent(QMouseEvent* me) override; // Реагирует на нажатие кнопок мыши
    // void mouseReleaseEvent(QMouseEvent* me) override; // Метод реагирует на "отжатие" кнопки мыши

    // void singling_lb(); // Рисуем рамку выделенной области
    // void geese(); // Рисуем квадрат по которому кликать для получения очков

private:
    void calculate();
    void Psinus();
    double scale;
    double a, b, A, B, step;
    std::vector<double> phi;
    std::vector<double> x, y;
    int x0,y0;
#ifdef GIRO
    bool bol = true;
    void inf()
    {
        sleep(1);
        timespec ts = { 0, 100 }, tv;
        while (bol) {
            nanosleep(&ts, &tv);
            paintGL();
            update();
        }
    }

    std::future<void> launch;
#endif
};
