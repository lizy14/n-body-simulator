
#include "widget.h"
#include "renderer.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>

Widget::Widget(Renderer *helper, QWidget *parent)
    : QWidget(parent), renderer(helper),
      bodies(nullptr), timer(nullptr),
      isAnimationOngoing(false),
      drawA(false),drawV(false)

{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    grabKeyboard();
    initBodies(3, 5, .1);
    startAnimation();
}
void Widget::initBodies(int nBodies_, double initialVelocity_, double deltaT_, int maxPointsInOrbit_){
    delete bodies;
    bodies = new Bodies(nBodies_, initialVelocity_, deltaT_, maxPointsInOrbit_);
}

Widget::~Widget(){
    delete bodies;
    delete timer;
}
void Widget::startAnimation(){
    timer->start(10);
    isAnimationOngoing=true;
    repaint();
}
void Widget::stopAnimation(){
    timer->stop();
    isAnimationOngoing=false;
    repaint();
}
void Widget::toggleAnimation(){
    if(isAnimationOngoing)
        stopAnimation();
    else
        startAnimation();
    repaint();
}

void Widget::animate()
{
    bodies->advance();
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    renderer->paint(this, bodies, event, (drawV), (drawA));
}
void Widget::mousePressEvent(QMouseEvent *ev){
    lastMouseX = ev->x();
    lastMouseY = ev->y();
}
void Widget::mouseMoveEvent(QMouseEvent *ev){
    if(!isAnimationOngoing){
        //TODO: handle vector dragging
    }
    double zoom = sqrt(renderer->transform.determinant());
    if(ev->buttons()==Qt::LeftButton){
        renderer->transform.translate((ev->x()-lastMouseX)/zoom, (ev->y()-lastMouseY)/zoom);
    }
    lastMouseX = ev->x();
    lastMouseY = ev->y();
    repaint();
}
void Widget::wheelEvent(QWheelEvent *ev){
    int steps = ev->delta()/120;
    double zoom = pow(1.1, steps);
    renderer->transform.scale(zoom, zoom);
    repaint();
}

bool Widget::event(QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Space) {
            toggleAnimation();
            return true;
        }
        if (keyEvent->key() == Qt::Key_A) {
            drawA = !drawA;
            repaint();
            return true;
        }
        if (keyEvent->key() == Qt::Key_V) {
            drawV = !drawV;
            repaint();
            return true;
        }
    }
    return QWidget::event(event);
}
