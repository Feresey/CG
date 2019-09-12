#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <GL/glu.h>
#include <QOpenGLWidget>
#include <QWidget>

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

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    template <class Func, class Iter>
    std::vector<double> calculate(Func&& f, Iter first, Iter last);
    void Psinus();
    double scale=1;
    double seed = 0.05;
    double a = 5, b = 20, A = -720, B = 720, step = 0.01;
};

#endif // OGLWIDGET_H
