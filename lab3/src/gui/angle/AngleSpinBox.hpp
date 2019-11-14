#ifndef ANGLE_SPIN_BOX_HPP
#define ANGLE_SPIN_BOX_HPP

#include <QDoubleSpinBox>

#include "Vector.hpp"
#include "config.hpp"

class AngleSpinBox : public QDoubleSpinBox {
    Q_OBJECT
    char axis;

public:
    AngleSpinBox(QWidget* p = 0, char ax = 'x');
    void SetAxis(char ax);

public slots:
    void set_value(Vector3f);
    void set_value(double);
signals:
    void value_changed(Vector3f value, char ax);
};

#endif