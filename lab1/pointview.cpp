#include "pointview.hpp"

PointView::PointView(bool x)
    : is_x(x)
{
}

void PointView::new_point(QPointF p)
{
    setValue(is_x ? p.rx() : p.ry());
    update();
}

void PointView::setX(bool x) { is_x = x; }