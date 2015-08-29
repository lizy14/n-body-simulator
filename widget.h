
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include "bodies.h"
//! [0]
class Renderer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Renderer *helper, QWidget *parent);
    ~Widget();

private:
    int lastMouseX, lastMouseY;
public slots:
    void animate();
    void mouseMoveEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Renderer *helper;
    Bodies *bodies;
};


#endif
