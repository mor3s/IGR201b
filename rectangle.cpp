#include "rectangle.h"

#include <QPainter>

Rectangle::Rectangle(QPoint _p1, QPoint _p2)
{
    p1 = _p1;
    p2 = _p2;
}
void Rectangle::paint(QPainter* painter){
    QRect* rect = new QRect(p1,p2);
    painter->drawRect(*rect);
}
