
#include "renderer.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include "bodies.h"
#include <QDebug>
#include <QString>

Renderer::Renderer()
{
    transform.translate(300,300);
    background = QBrush(QColor(0, 7, 24));
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}



void Renderer::paint(QWidget *widget, Bodies *bodies, QPaintEvent *event, bool drawV, bool drawA)
{
    QPainter painter_(widget);
    QPainter *painter = &painter_;
    painter->fillRect(event->rect(), background);
    painter->setTransform(transform);

    QColor color;
    for(int i=0; i<bodies->nBodies; i++){
        color.setHsv((i * 360 / bodies->nBodies) % 360, 255,255);

        painter->setPen(color);
        painter->drawPolyline(bodies->bodies[i].orbit.toVector());
        painter->setBrush(color);
        painter->drawEllipse(bodies->bodies[i].position,10,10);
        if(drawV){
            painter->drawLine(bodies->bodies[i].position,bodies->bodies[i].position+10*bodies->bodies[i].velocity);
        }
        if(drawA){
            painter->drawLine(bodies->bodies[i].position,bodies->bodies[i].position+100*bodies->bodies[i].acceleration);
        }

    }

}
