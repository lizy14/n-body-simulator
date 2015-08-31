
#include "widget.h"
#include "renderer.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QGridLayout>
#include <QSlider>
#include <QLabel>

Widget::Widget(Renderer *helper, QWidget *parent)
    : QWidget(parent), renderer(helper),
      bodies(nullptr), timer(nullptr),
      drawA(false),drawV(false),
      nBodies(3),initialVelocity(5),deltaT(.1)

{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));

    QGridLayout *layout = new QGridLayout;
    QSlider *slider;
    QLabel *label;

    slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(1,10);
    slider->setValue(nBodies);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(on_nbodies_change(int)));
    layout->addWidget(slider, 1, 1);
    label = new QLabel;
    label->setText("<font color=\"white\">nBodies</font>");
    layout->addWidget(label, 1, 0);

    slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0,2000);
    slider->setValue(initialVelocity*100);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(on_initialvelocity_change(int)));
    layout->addWidget(slider, 2, 1);
    label = new QLabel;
    label->setText("<font color=\"white\">initialVelocity</font>");
    layout->addWidget(label, 2, 0);

    slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(1,log(1*100)/log(1.01));
    slider->setValue(log(deltaT*100)/log(1.01));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(on_deltat_change(int)));
    layout->addWidget(slider, 3, 1);
    label = new QLabel;
    label->setText("<font color=\"white\">deltaT</font>");
    layout->addWidget(label, 3, 0);

    layout->setRowStretch(0,9999);
    setLayout(layout);

    grabKeyboard();
    initBodies(nBodies, initialVelocity, deltaT);
}
void Widget::on_nbodies_change(int x){
    nBodies = x;
    initBodies(nBodies, initialVelocity, deltaT);
    qDebug() << "nBodies" << nBodies;
}
void Widget::on_initialvelocity_change(int x){
    initialVelocity = x/100.0;
    initBodies(nBodies, initialVelocity, deltaT);
    qDebug() << "initialVelocity" << initialVelocity;
}
void Widget::on_deltat_change(int x){
    deltaT = pow(1.01,x)/100;
    initBodies(nBodies, initialVelocity, deltaT);
    qDebug() << "deltaT" << deltaT;
}

void Widget::initBodies(int nBodies_, double initialVelocity_, double deltaT_, int maxPointsInOrbit_){
    delete bodies;
    bodies = new Bodies(nBodies_, initialVelocity_, deltaT_, maxPointsInOrbit_);
    renderer->resetTransform();
    startAnimation();
    update();
}

Widget::~Widget(){
    delete bodies;
    delete timer;
}
void Widget::startAnimation(){
    timer->start(100*deltaT);
    update();
}
void Widget::stopAnimation(){
    timer->stop();
    update();
}
void Widget::toggleAnimation(){
    if(timer->isActive())
        stopAnimation();
    else
        startAnimation();
}

void Widget::animate()
{
    try{
        bodies->advance();
    }catch(...){
        stopAnimation();
    }
    update();
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
    if(!timer->isActive()){
        //TODO: handle vector dragging
    }
    double zoom = sqrt(renderer->transform.determinant());
    if(ev->buttons()==Qt::LeftButton){
        renderer->transform.translate((ev->x()-lastMouseX)/zoom, (ev->y()-lastMouseY)/zoom);
    }
    lastMouseX = ev->x();
    lastMouseY = ev->y();
    update();
}
void Widget::wheelEvent(QWheelEvent *ev){
    int steps = ev->delta()/120;
    double zoom = pow(1.1, steps);
    renderer->transform.scale(zoom, zoom);
    update();
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
            update();
            return true;
        }
        if (keyEvent->key() == Qt::Key_V) {
            drawV = !drawV;
            update();
            return true;
        }
    }
    return QWidget::event(event);
}
