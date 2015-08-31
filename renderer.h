
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
};


#endif
