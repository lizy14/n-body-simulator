
#include "renderer.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include "bodies.h"
#include <QDebug>
#include <QString>

Renderer::Renderer()
{
    resetTransform();
    background = QBrush(QColor(0, 7, 24));
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
    velocityPen = QPen(Qt::PenStyle::DashLine);
    accelerationPen = QPen(Qt::PenStyle::DotLine);
    orbitPen = QPen(Qt::PenStyle::SolidLine);
}

void Renderer::resetTransform(){
    transform.reset();
    transform.translate(300,300);
}
void Renderer::drawArrow(QPainter *painter, QPointF startingPoint, QPointF vector,
                         double arrowLength, double deltaRadian){
    if(!vector.x() || !vector.y())return;
    painter->save();
    double k = vector.y()/vector.x();
    QPointF endingPoint = startingPoint+vector;
    painter->drawLine(startingPoint, endingPoint);
    if(vector.x()>0)
        arrowLength *= -1;
    double alphaL = (atan(k)+deltaRadian);
    double alphaR = (atan(k)-deltaRadian);
    QPen pen = painter->pen();
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(endingPoint, endingPoint + arrowLength * QPointF(cos(alphaL),sin(alphaL)));
    painter->drawLine(endingPoint, endingPoint + arrowLength * QPointF(cos(alphaR),sin(alphaR)));
    painter->restore();
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
        orbitPen.setColor(color);
        painter->setPen(orbitPen);
        painter->drawPolyline(bodies->bodies[i].orbit.toVector());

        painter->setPen(circlePen);
        painter->setBrush(color);
        painter->drawEllipse(bodies->bodies[i].position,10,10);


        if(drawV){
            velocityPen.setColor(color);
            painter->setPen(velocityPen);
            drawArrow(painter, bodies->bodies[i].position,10*bodies->bodies[i].velocity);
        }
        if(drawA){
            accelerationPen.setColor(color.darker(150));
            painter->setPen(accelerationPen);
            drawArrow(painter, bodies->bodies[i].position,100*bodies->bodies[i].acceleration);
        }

    }

}
