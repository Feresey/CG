#include "AngleSpinBox.hpp"

AngleSpinBox::AngleSpinBox(QWidget* p, char ax)
    : QDoubleSpinBox(p)
    , axis(ax)
{
}

void AngleSpinBox::SetAxis(char ax)
{
    axis = ax;
    update();
}

void AngleSpinBox::set_value(Vector3f v)
{
    switch (axis) {
    case 'x':
        setValue(v[0] / D2R);
        break;
    case 'y':
        setValue(v[1] / D2R);
        break;
    case 'z':
        setValue(v[2] / D2R);
        break;
    }
}

void AngleSpinBox::set_value(double _val)
{
    Vector3f res{ 0, 0, 0 };
    float val = static_cast<float>(_val);
    switch (axis) {
    case 'x':
        res[0] = val * D2R;
        break;
    case 'y':
        res[1] = val * D2R;
        break;
    case 'z':
        res[2] = val * D2R;
        break;
    }
    value_changed(res, axis);
}
