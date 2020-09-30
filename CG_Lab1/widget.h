#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QWidget>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

private:
    QDoubleSpinBox* radius;
    QLabel* deltaShow;
    Ui::Widget *ui;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void zoom(double);
    double scale = 15;

protected:
    void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent* events);

private slots:
    void redrawOnValueChange(double);

};
#endif // WIDGET_H

