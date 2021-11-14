#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
private:
    QPoint p1{},p2{};
public:
    void set_p1(int x, int y) override {
        p1.setX(x);
        p1.setY(y);
    }
    void set_p2(int x, int y) override{
        p2.setX(x);
        p2.setY(y);
    }
    QPoint get_p1() override {return p1;}
    QPoint get_p2() override {return p2;}
    Rectangle(QPoint _p1, QPoint _p2);

    void paint(QPainter* painter) override;
};

#endif // RECTANGLE_H
