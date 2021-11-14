#ifndef DRAW_H
#define DRAW_H
#include <QWidget>
#include <QPoint>
#include "shape.h"
class Draw : public QWidget
{
private:
    QPoint p1{}, p2{};
    QPoint p1Move{}, p2Move{};
    Shape* actualShape{};
    int height{}, width{};
    std::vector<std::pair<Shape*,QPen>> draws{};
    std::vector<std::pair<Shape*,QPen>> editDraws{};
    QColor penColor = Qt::black;
    Qt::PenStyle penStyle = Qt::SolidLine;
    int size = 1;
    QColor editPenColor;
    Qt::PenStyle editPenStyle;
    int editSizeValue=2;
    std::string shapeType = "line";
    bool edit = false;
    int zoom = 0;
    bool drag = false;

public:
    Draw(QWidget* parent): QWidget(parent){this->setMinimumSize(500,500);}
    void set_p1(int x, int y){
        p1.setX(x);
        p1.setY(y);
    }
    void set_p2(int x, int y){
        p2.setX(x);
        p2.setY(y);
    }

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void set_thickness(int _size){size=_size;}
    void set_color(QColor _color){penColor=_color;}
    void set_style(Qt::PenStyle _style){penStyle = _style;}
    void set_shape(std::string shape){shapeType = shape;}
    void editShape();
    void editStyle(Qt::PenStyle style);
    void editSelection();
    void editSize(int size);
    void editColor(QColor color);
    void scaleDefinitive();
    void scaleSelection(int value);


protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // DRAW_H
