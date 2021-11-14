#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QPoint>
class Shape
{
public:
    Shape();
    virtual ~Shape(){};
    virtual void paint(QPainter* painter) = 0;
    virtual void set_p1(int x, int y) = 0;
    virtual void set_p2(int x, int y) = 0;
    virtual QPoint get_p1() = 0;
    virtual QPoint get_p2() = 0;
};

#endif // SHAPE_H
