
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
    //circleBrush
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}



void Renderer::paint(QWidget *widget, Bodies *bodies, QPaintEvent *event)
{
    QPainter painter_(widget);
    QPainter *painter = &painter_;
    painter->fillRect(event->rect(), background);
    painter->setTransform(transform);


    painter->save();

    QColor color;
    for(int i=0; i<bodies->nBodies; i++){
        qDebug() << i ;
        qDebug() << "x " << bodies->bodies[i].position;
        qDebug() << "v " << bodies->bodies[i].velocity;
        qDebug() << "a " << bodies->bodies[i].acceleration;
        color.setHsv((i * 360 / bodies->nBodies) % 360, 255,255);

        painter->setPen(color);
        painter->drawPolyline(bodies->bodies[i].orbit);
        painter->setBrush(color);
        painter->drawEllipse(bodies->bodies[i].position,10,10);

    }
    painter->restore();





}
