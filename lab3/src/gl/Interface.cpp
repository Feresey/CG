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
    if (mouse_tapped) {
        switch (button_pressed) {
        case Qt::MouseButton::LeftButton:
            zero += prev_pos - me->pos();
            break;
        case Qt::MouseButton::RightButton:
            angle_phi -= float((prev_pos - me->pos()).x()) * 0.2f * M_PIf32 / 180.0f;
            angle_theta -= float((prev_pos - me->pos()).y()) * 0.2f * M_PIf32 / 180.0f;
            break;
        case Qt::MouseButton::MiddleButton:
            break;
        default:
            break;
        }

        prev_pos = me->pos();
        LoadMatrix();
    }
}

void GLWidget::mousePressEvent(QMouseEvent* me)
{
    mouse_tapped = true;
    button_pressed = me->button();
    prev_pos = me->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* me)
{
    mouse_tapped = false;
    prev_pos = me->pos();
}

void GLWidget::restore()
{
    scale = findScale();
    update();
    scale_message("");
    scale_changed(scale);
    angle_phi = 0;
    angle_theta = 0.0f;
    zero = normalize = { width() / 2, -height() / 2 };
    LoadMatrix();
}

void GLWidget::set_scale(double val)
{
    scale = static_cast<float>(val);
    if (scale < 1e-6f)
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