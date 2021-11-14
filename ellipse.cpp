#include "ellipse.h"

#include <QPainter>

Ellipse::Ellipse(QPoint _p1, QPoint _p2)
{
    p1 = _p1;
    p2 = _p2;
}
void Ellipse::paint(QPainter* painter){
    QRect* ellipse = new QRect(p1,p2);
    painter->drawEllipse(*ellipse);
}
