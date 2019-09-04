#include "AngleSpinBox.hpp"

AngleSpinBox::AngleSpinBox(QWidget* p, char ax, float prod)
    : QDoubleSpinBox(p)
    , axis(ax)
    , prod(prod)
{
}

void AngleSpinBox::SetAxis(char ax)
{
    axis = ax;
    update();
}

void AngleSpinBox::SetProd(float p)
{
    prod = p;
    update();
}

void AngleSpinBox::set_value(Vector3f v)
{
    switch (axis) {
    case 'x':
        setValue(v[0] / prod);
        break;
    case 'y':
        setValue(v[1] / prod);
        break;
    case 'z':
        setValue(v[2] / prod);
        break;
    }
}

void AngleSpinBox::set_value(double _val)
{
    Vector3f res{ 0, 0, 0 };
    float val = static_cast<float>(_val);
    switch (axis) {
    case 'x':
        res[0] = val * prod;
        break;
    case 'y':
        res[1] = val * prod;
        break;
    case 'z':
        res[2] = val * prod;
        break;
    }
    value_changed(res, axis);
}
