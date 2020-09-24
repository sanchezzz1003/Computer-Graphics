#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <QPainter>
#include <QLabel>
#include <QDoubleSpinBox>

//const double pi(4 * atan(1));

#define pi 3.14159265358979323846

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QLabel* lblRadius(new QLabel("a:", this));
    lblRadius->move(10, 10);
    radius = new QDoubleSpinBox(this);
    radius->setRange(1, 300);
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
//    connect(step, SIGNAL(valueChanged(double)),this, SLOT(redrawOnValueChange(double)));
}

double min(double a, double b){
    if (a < b) return a;
    else return b;
}

QPointF PolarToDecart(double r, double phi){
    QPointF result(cos(phi)*r, sin(phi)*r);
    return result;
}

void Widget::paintEvent(QPaintEvent*){
    const double rad(radius->value());
    const double st(0.01);
    const double end(2 * pi + st);
    double r(0);


    QPointF p1(rad, 0);

    QPointF up(width() / 2.0, 0);
    QPointF down(width() / 2.0, height());
    QPointF left(0, height() / 2.0);
    QPointF right(width(), height() / 2.0);
    QPainter ptr(this);

    ptr.setPen(Qt::black);
    ptr.drawLine(left, right);
    ptr.drawLine(down, up);

    ptr.setPen(Qt::blue);

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
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
}

void Widget::redrawOnValueChange(double){
    update();
}

Widget::~Widget()
{
    delete ui;
}


