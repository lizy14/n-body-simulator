
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
    void paint(QWidget *widget, Bodies* bodies, QPaintEvent *event);
public:
    QTransform transform;
private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
};


#endif
