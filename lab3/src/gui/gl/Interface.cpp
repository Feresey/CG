#include "GLWidget.hpp"

void GLWidget::wheelEvent(QWheelEvent* we)
{
    float dl = float(we->delta());
    scale *= 1.0f + 4e-4f * dl;

    set_scale(scale);
    scale_changed(scale);
    Apply();
}

void GLWidget::mouseMoveEvent(QMouseEvent* me)
{
    if (button_pressed == Qt::MouseButton::NoButton)
        return;
    switch (button_pressed) {
    case Qt::MouseButton::LeftButton:
        zero += prev_pos - me->pos();
        break;
    case Qt::MouseButton::RightButton:
        angle.x() -= float((prev_pos - me->pos()).x()) * 0.2f * D2R;
        angle.y() -= float((prev_pos - me->pos()).y()) * 0.2f * D2R;
        angle_changed(angle);
        break;
    case Qt::MouseButton::MiddleButton:
        break;
    default:
        break;
    }

    prev_pos = me->pos();
    Apply();
}

void GLWidget::mousePressEvent(QMouseEvent* me)
{
    button_pressed = me->button();
    prev_pos = me->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* me)
{
    button_pressed = Qt::MouseButton::NoButton;
    prev_pos = me->pos();
}

void GLWidget::auto_scale()
{
    zero = { 0, 0 };
    normalize = { 0, 0 };
    scale = 1;
    Apply();
    auto borders = figure.MinMax();
    float arr[] = {
        abs(borders.first.x()),
        abs(borders.first.y()),
        abs(borders.second.x()),
        abs(borders.second.y()),
    };
    float mx = std::max(arr[0], std::max(arr[1], std::max(arr[2], arr[3])));

    scale = float(std::min(width(), height())) * 0.45f / mx;
    normalize = { width() / 2, -height() / 2 };

    scale_message("");
    scale_changed(scale);

    Apply();
}
void GLWidget::initial_state()
{
    auto_scale();
    angle_changed(angle);
}

void GLWidget::set_scale(double val)
{
    scale = static_cast<float>(val);
    if (scale < EPS)
        scale_message();
    else
        scale_message("");
    Apply();
}

void GLWidget::change_colors()
{
    figure.ChangeColor();
    Apply();
}

void GLWidget::color(bool ind)
{
    color_enabled = ind;
    update();
}

void GLWidget::edges(bool ind)
{
    edges_enabled = ind;
    update();
}

void GLWidget::base(bool ind)
{
    base_enabled = ind;
    update();
}

void GLWidget::set_angle(Vector3f v, char axis)
{
    switch (axis) {
    case 'x':
        angle.x() = v[0];
        break;
    case 'y':
        angle.y() = v[1];
        break;
    case 'z':
        angle.z() = v[2];
        break;
    }
    Apply();
}

void GLWidget::set_approx(int ap)
{
    if (approx != ap) {
        approx = ap;
        gen_figuries();
    }
    update();
}
