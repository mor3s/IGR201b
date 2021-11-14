#include "draw.h"
#include <QPainter>
#include <QCursor>
#include <QMouseEvent>
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include <QBrush>
#include <iostream>
#include <cmath>

void Draw::paintEvent(QPaintEvent * e){
    QWidget::paintEvent(e);
    QPainter painter(this);
    QBrush brush(QColor(255, 0, 255, 20));
    if(edit){

        for (auto draw : draws)
        {
            painter.setPen(draw.second);
            draw.first->paint(&painter);
        }


        painter.setPen(QPen(QColor(255,0,255,127),2,Qt::DashLine));
        painter.setBrush(brush);
        if(actualShape!=nullptr) actualShape->paint(&painter);
    }
    else{

        painter.setPen(QPen(penColor,size,penStyle));
        if(actualShape!=nullptr) actualShape->paint(&painter);
        for (auto draw : draws)
        {
            painter.setPen(draw.second);
            draw.first->paint(&painter);
        }
    }


}


void Draw::mousePressEvent(QMouseEvent* e){
    if(e->button() == Qt::LeftButton) {
        if(edit){
            int x = e->pos().x();
            int y = e->pos().y();
            set_p1(x,y);
            actualShape = new Rectangle(p1,p1);
            update();

        }else {
            int x = e->pos().x();
            int y = e->pos().y();
            set_p1(x,y);
            if (shapeType == "line"){
              actualShape = new Line(p1,p1);
            } else if (shapeType == "rectangle"){
              actualShape = new Rectangle(p1,p1);
            } else if (shapeType == "ellipse"){
              actualShape = new Ellipse(p1,p1);
            }
        }
    }else {
        int x = e->pos().x();
        int y = e->pos().y();
        if(((QRect*) actualShape)->contains(x,y) && edit){
            drag = true;
        }
    }



}

void Draw::mouseMoveEvent(QMouseEvent* e){
    int x = e->pos().x();
    int y = e->pos().y();
    if (drag == true){
        actualShape->set_p1(x+width/2, y+height/2);
        actualShape->set_p2(x-width/2, y-height/2);

    }else {
        set_p2(x,y);
        actualShape->set_p1(p1.x(),p1.y());
        actualShape->set_p2(p2.x(),p2.y());
        update();
    }

}

void Draw::mouseReleaseEvent(QMouseEvent* e){
    if(not drag) {
        if(edit){
            height = abs(actualShape->get_p1().y() - actualShape->get_p1().y());
            width = abs(actualShape->get_p1().x() - actualShape->get_p1().x());

            update();
        }else{
            int x = e->pos().x();
            int y = e->pos().y();
            set_p2(x,y);
            Shape* shape;
            if (shapeType == "line"){
              shape = new Line(p1,p2);
            } else if (shapeType == "rectangle"){
              shape = new Rectangle(p1,p2);
            } else if (shapeType == "ellipse"){
              shape = new Ellipse(p1,p2);
            }
            draws.push_back(std::pair(shape,QPen(penColor,size,penStyle)));
            update();
        }
    }else  {
        drag = false;
    }



}



void Draw::editShape() {
    edit = not edit;
    if(edit==false){
        actualShape=nullptr;
        update();
    }

}

void Draw::editStyle(Qt::PenStyle style) {
    editPenStyle = style;
}

void Draw::editSize(int size) {
    editSizeValue = size;
}
void Draw::editColor(QColor color) {
    editPenColor = color;
}

void Draw::editSelection() {
        editDraws = {};
        for(auto draw : draws){
            if(QRect(actualShape->get_p1(), actualShape->get_p2()).contains(QRect(draw.first->get_p1(),draw.first->get_p2()))){
                editDraws.push_back(std::pair(draw.first,QPen(editPenColor,editSizeValue,editPenStyle)));
            }else{
                editDraws.push_back(draw);
            }
        }
        draws = editDraws;
        update();
}

void Draw::scaleSelection(int value){
    zoom = value;
}

void Draw::scaleDefinitive(){
    editDraws = {};
    for(auto draw : draws){
        if(QRect(actualShape->get_p1(), actualShape->get_p2()).contains(QRect(draw.first->get_p1(),draw.first->get_p2()))){
            Shape* d = draw.first;
            float p1x = draw.first->get_p1().x();
            float p1y = draw.first->get_p1().y();
            float p2x = draw.first->get_p2().x();
            float p2y = draw.first->get_p2().y();
            float dx = p2x-p1x;
            float dy = p2y-p1y;
            if(zoom<50){
                d->set_p1(p1x + dx * (zoom)/100 ,p1y + dy * (zoom)/100 );
                d->set_p2(p2x - dx * (zoom)/100 , p2y - dy * (zoom)/100);
            }else{
                d->set_p1(p1x - dx * (zoom)/100, p1y - dy * (zoom)/100);
                d->set_p2(p2x + dx * (zoom)/100, p2y + dy * (zoom)/100);
            }
            editDraws.push_back(std::pair(d,draw.second));
        }else{
            editDraws.push_back(draw);
        }
    }
    draws = editDraws;
    update();
}



