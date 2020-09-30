#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <QPainter>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QWheelEvent>
#include <QString>
#include <cstdlib>

//const double pi(4 * atan(1));

#define pi 3.14159265358979323846

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QLabel* lblRadius(new QLabel("a:", this));
    lblRadius->move(10, 10);
    radius = new QDoubleSpinBox(this);
    radius->setRange(1, 1000);
    radius->setSingleStep(1);
    radius->setValue(150);
    radius->move(10, 30);

/*    QLabel* lblStep(new QLabel("Step:", this));
    lblStep->move(10, 50);
    step = new QDoubleSpinBox(this);
    step->setRange(0.01, 1);
    step->setSingleStep(0.01);
    step->setValue(0.1);
    step->move(10, 70);
*/

    ui->setupUi(this);
    connect(radius, SIGNAL(valueChanged(double)),this, SLOT(redrawOnValueChange(double)));
}

double min(double a, double b){
    if (a < b) return a;
    else return b;
}

QPointF PolarToDecart(double r, double phi){
    QPointF result(cos(phi)*r, sin(phi)*r);
    return result;
}

void Widget::zoom(double change){
    if (scale > 1 || (scale == 1 && change > 0)){
        scale *= (1+change/scale);
    }
}

void Widget::wheelEvent(QWheelEvent* events)
{

    int numDegrees = events -> angleDelta().y() / 8;
    double numTicks = numDegrees / 15.0;

    zoom(numTicks);
    update();
}

void Widget::paintEvent(QPaintEvent*){
    const double rad(radius->value());
    const double st(0.01);
    const double end(2 * pi + st);
    double wSize = min(width(),height())/400.0;
    double r(0);

    QPointF p1(rad, 0);

    QPointF up(width() / 2.0, 0);
    QPointF down(width() / 2.0, height());
    QPointF left(0, height() / 2.0);
    QPointF right(width(), height() / 2.0);
    QPainter ptr(this);
    QPen mypen;

    mypen.setWidth(3);
    mypen.setBrush(Qt::blue);
    ptr.setPen(mypen);
    const QPointF center(width() / 2.0, height() / 2.0);

  /*  for (double t(st); t < end; t += st){
        QPointF p2(cos(t*2*pi/360.0), sin(t*2*pi/360.0));
        p2 *= rad;
        ptr.drawLine(p1 + center, p2 + center);
        p1 = p2;
    }
*/
    for (double phi(st); phi < end; phi+= st){
        r = rad*cos(3*phi);
        QPointF p2 = PolarToDecart(r, phi);
        ptr.drawLine(center+p1*wSize*scale/15, center+p2*wSize*scale/15);
        p1 = p2;
    }

    mypen.setBrush(Qt::black);
    mypen.setWidth(2);
    ptr.setPen(mypen);
    ptr.drawLine(left, right);
    ptr.drawLine(down, up);
    mypen.setWidth(1);
    ptr.setPen(mypen);

    if(scale > 10){
        p1.setX(width()/2);
        p1.setY(height()/2-3);
        QPointF p2(width()/2, height()/2+3);
        int j = 0;
        char buffer [100];
        for(int i = center.y(); i < center.y()+width(); i+=scale){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p1, buffer);
            j += 10;
            p1.setX(p1.x()+scale);
            p2.setX(p2.x()+scale);
        }
        p1.setX(width()/2);
        p1.setY(height()/2-3);
        p2.setX(width()/2);
        p2.setY(height()/2+3);
        j = 0;
        for(int i = center.y(); i > center.y()-width(); i-=scale){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p1, buffer);
            j += 10;
            p1.setX(p1.x()-scale);
            p2.setX(p2.x()-scale);
        }
        p1.setX(width()/2-3);
        p1.setY(height()/2);
        p2.setX(width()/2+3);
        p2.setY(height()/2);
        j = 0;
        for(int i = center.x(); i < center.x()+height(); i+=scale){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p2, buffer);
            j += 10;
            p1.setY(p1.y()+scale);
            p2.setY(p2.y()+scale);
        }
        p1.setX(width()/2-3);
        p1.setY(height()/2);
        p2.setX(width()/2+3);
        p2.setY(height()/2);
        j = 0;
        for(int i = center.x(); i > center.y()-height(); i-=scale){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p2, buffer);
            j += 10;
            p1.setY(p1.y()-scale);
            p2.setY(p2.y()-scale);
        }
    }
    mypen.setWidth(2);
    ptr.setPen(mypen);
    p1.setX(width()/2);
    p1.setY(height()/2-4);
    QPointF p2(width()/2, height()/2+4);
    for(int i = center.y(); i < center.y()+width(); i+=scale*10){
        ptr.drawLine(p1,p2);
        p1.setX(p1.x()+scale*10);
        p2.setX(p2.x()+scale*10);
    }
    p1.setX(width()/2);
    p1.setY(height()/2-4);
    p2.setX(width()/2);
    p2.setY(height()/2+4);
    for(int i = center.y(); i > center.y()-width(); i-=scale*10){
        ptr.drawLine(p1,p2);
        p1.setX(p1.x()-scale*10);
        p2.setX(p2.x()-scale*10);
    }
    p1.setX(width()/2-4);
    p1.setY(height()/2);
    p2.setX(width()/2+4);
    p2.setY(height()/2);
    for(int i = center.x(); i < center.x()+height(); i+=scale*10){
        ptr.drawLine(p1,p2);
        p1.setY(p1.y()+scale*10);
        p2.setY(p2.y()+scale*10);
    }
    p1.setX(width()/2-4);
    p1.setY(height()/2);
    p2.setX(width()/2+4);
    p2.setY(height()/2);
    for(int i = center.x(); i > center.y()-height(); i-=scale*10){
        ptr.drawLine(p1,p2);
        p1.setY(p1.y()-scale*10);
        p2.setY(p2.y()-scale*10);
    }
}

void Widget::redrawOnValueChange(double){
    update();
}

Widget::~Widget()
{
    delete ui;
}



