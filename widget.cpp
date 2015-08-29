
#include "widget.h"
#include "renderer.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>

Widget::Widget(Renderer *helper, QWidget *parent)
    : QWidget(parent), helper(helper)

{
    this->setMouseTracking(true);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    bodies = new Bodies(3);
    timer->start(10);
}
Widget::~Widget(){
    delete bodies;

}

void Widget::animate()
{
    bodies->advance();
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    helper->paint(this, bodies, event);
}
void Widget::mouseMoveEvent(QMouseEvent *ev){
    double zoom = sqrt(helper->transform.determinant());
    if(ev->buttons()==Qt::LeftButton){
        helper->transform.translate((ev->x()-lastMouseX)/zoom, (ev->y()-lastMouseY)/zoom);
    }
    lastMouseX = ev->x();
    lastMouseY = ev->y();
    repaint();
}
void Widget::wheelEvent(QWheelEvent *ev){
    int steps = ev->delta()/120;
    qDebug() << steps;
    double zoom = pow(1.1, steps);
    qDebug() << zoom;
    helper->transform.scale(zoom, zoom);
    qDebug() << helper->transform;
    repaint();
}

