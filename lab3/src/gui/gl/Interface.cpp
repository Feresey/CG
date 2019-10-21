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
        angle_phi -= float((prev_pos - me->pos()).x()) * 0.2f * D2R;
        angle_theta -= float((prev_pos - me->pos()).y()) * 0.2f * D2R;
        phi_changed(angle_phi / D2R);
        theta_changed(angle_theta / D2R);
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
    normalize = { width() / 2, -height() / 2 };
    LoadMatrix();
    auto borders = figure.MinMax();

    // scale = findScale();
    update();
    scale_message("");
    scale_changed(scale);

    LoadMatrix();
}
void GLWidget::restore_all()
{
    angle_theta = angle_phi = 0;
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
    angle_theta = angle_phi = 0;
    restore();
}

void GLWidget::set_phi(double val)
{
    angle_phi = float(val) * D2R;
    LoadMatrix();
}

void GLWidget::set_theta(double val)
{
    angle_theta = float(val) * D2R;
    LoadMatrix();
}
