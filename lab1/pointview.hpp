#ifndef POINTVIEW_HPP
#define POINTVIEW_HPP

#include <QDoubleSpinBox>

class PointView : public QDoubleSpinBox {
    Q_OBJECT
public slots:
    void setX(bool = true);
    void new_point(QPointF p);

signals:

private:
    bool is_x;

public:
    PointView(bool x = true);
    ~PointView() = default;
};

#endif

