#include "GLWidget.hpp"

void GLWidget::wheelEvent(QWheelEvent* we)
{
    float dl = float(we->delta());
    scale *= 1.0f + 4e-4f * dl;

    set_scale(scale);
    scale_changed(scale);
    LoadMatrix();
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
        angle_x -= float((prev_pos - me->pos()).x()) * 0.2f * D2R;
        angle_y -= float((prev_pos - me->pos()).y()) * 0.2f * D2R;
        x_changed(angle_x / D2R);
        y_changed(angle_y / D2R);
        break;
    case Qt::MouseButton::MiddleButton:
        break;
    default:
        break;
    }

    prev_pos = me->pos();
    LoadMatrix();
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

void GLWidget::restore()
{
    zero = { 0, 0 };
    normalize = { 0, 0 };
    scale = 1;
    LoadMatrix();
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

    LoadMatrix();
}
void GLWidget::restore_all()
{
    angle_y = angle_x = angle_z = 0;
    x_changed(0);
    y_changed(0);
    z_changed(0);
    restore();
}

void GLWidget::set_scale(double val)
{
    scale = static_cast<float>(val);
    if (scale < EPS)
        scale_message();
    else
        scale_message("");
    LoadMatrix();
}

void GLWidget::redraw()
{
    figure.ChangeColor();
    LoadMatrix();
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

void GLWidget::project(int val)
{
    pr = val;
    switch (pr) {
    case project_yz:
        angle_x = -90 * D2R;
        angle_y = -90 * D2R;
        angle_z = 0;
        break;
    case project_xz:
        angle_x = angle_z = 0;
        angle_y = -90 * D2R;
        break;
    default:
        angle_x = angle_y = angle_z = 0;
    }
    restore();
}

void GLWidget::set_x(double val)
{
    angle_x = float(val) * D2R;
    LoadMatrix();
}

void GLWidget::set_y(double val)
{
    angle_y = float(val) * D2R;
    LoadMatrix();
}

void GLWidget::set_z(double val)
{
    angle_z = float(val) * D2R;
    LoadMatrix();
}
