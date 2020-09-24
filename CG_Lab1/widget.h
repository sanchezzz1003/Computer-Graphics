#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void redrawOnValueChange(double);

private:
    QDoubleSpinBox* radius;
    QDoubleSpinBox* step;
    Ui::Widget *ui;
};
#endif // WIDGET_H
