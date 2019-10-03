#include "GLWidget.hpp"

void GLWidget::wheelEvent(QWheelEvent* we)
{
    int dl = we->delta();
    scale *= 1 + 0.001 * dl;

    set_scale(scale);
    scale_changed(scale);
}

void GLWidget::mouseMoveEvent(QMouseEvent* me)
{
    if (mouse_tapped) {
        QPoint tmp = zero - normalize;
        zero += prev_pos - me->pos();

        switch (button_pressed) {
        case Qt::MouseButton::LeftButton:
            break;
        case Qt::MouseButton::RightButton:
            angle_phi += ((prev_pos - me->pos()).x() * 0.2) * M_PI / 180;
            angle_theta -= ((prev_pos - me->pos()).y() * 0.2) * M_PI / 180;
            break;
        case Qt::MouseButton::MiddleButton:
            break;
        default:
            break;
        }

        prev_pos = me->pos();
        LoadMatrix();
        update();
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

    zero = normalize = { width() / 2, -height() / 2 };
    update();
}

void GLWidget::set_scale(double val)
{
    scale = val;
    if (scale < 0.0000001)
        scale_message();
    else
        scale_message("");
    update();
}
