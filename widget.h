
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include "bodies.h"

class Renderer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Renderer *renderer, QWidget *parent);
    ~Widget();
    void initBodies(int nBodies_, double initialVelocity_ = -1, double deltaT_ = .5, int maxPointsInOrbit_=10000);

private:
    int lastMouseX, lastMouseY;
public slots:
    void animate();
    void on_nbodies_change(int);
    void on_initialvelocity_change(int);
    void on_deltat_change(int);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    bool event(QEvent *event);

private:
    double deltaT;
    int maxPointsInOrbit;
    int nBodies;
    double initialVelocity;
private:
    bool drawA, drawV;
    Renderer *renderer;
    QTimer *timer;
    Bodies *bodies;
public:
    void startAnimation();
    void stopAnimation();
    void toggleAnimation();
};


#endif
