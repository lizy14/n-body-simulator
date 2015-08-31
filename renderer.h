
#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "bodies.h"

class Renderer
{
public:
    Renderer();

public:
    void paint(QWidget *widget, Bodies* bodies, QPaintEvent *event, bool drawV=false, bool drawA=false);
public:
    QTransform transform;
    void resetTransform();
private:
    QBrush background;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
    QPen velocityPen;
    QPen accelerationPen;
    QPen orbitPen;
private:
    void drawArrow(QPainter *painter, QPointF startingPoint, QPointF vector,
                   double arrowLength = 10/*pixels*/, double deltaRadian = 0.523599/*= 30 degrees*/);
};


#endif
