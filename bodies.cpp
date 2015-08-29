#include "bodies.h"
#include <QDebug>
#include <QMessageBox>
Bodies::Bodies(int nBodies_)
{
    nBodies = nBodies_;
    bodies = new Body[nBodies];
    for(int i=0; i<nBodies; i++){
        double sin_ = sin(i/(double)nBodies * 2 * 3.1415927);
        double cos_ = cos(i/(double)nBodies * 2 * 3.1415927);
        bodies[i].position = QPointF(
                    sin_*100,
                    cos_*100
                    );
        bodies[i].velocity = QPointF(
                    cos_*5,
                    -sin_*5
                    );
    }
    return;
}



const double Bodies::G = 7000;
const double Bodies::k = 0.01;
double Bodies::deltaT = .5;

QPointF Bodies::gravity(int idA, int idB){
    if(idA==idB) throw("gravity calculation error");
    QPointF dx = bodies[idA].position - bodies[idB].position;
    static int retry = true;
    double r_squared = dx.x() * dx.x() + dx.y() * dx.y();

    if(r_squared<100 && retry){
        QMessageBox msgBox;
        msgBox.setText("too close");
        msgBox.setStandardButtons(QMessageBox::Ignore | QMessageBox::Abort | QMessageBox::Retry);
        msgBox.setDefaultButton(QMessageBox::Retry);
        int ret = msgBox.exec();
        if(ret==QMessageBox::Ignore)
            retry=false;
        else if(ret==QMessageBox::Retry)
            ;
        else
            throw "too close";
    }

    return dx * G/pow(r_squared,1.5) * (-1);
}

void Bodies::advance(){
    for(int i=0; i<nBodies; i++)
        bodies[i].acceleration = QPointF(0,0);
    for(int idA = 0; idA < nBodies; idA++){
        for(int idB = 0; idB < idA; idB++){
            QPointF force = gravity(idA, idB);
            bodies[idA].acceleration += force / bodies[idA].mass;
            bodies[idB].acceleration -= force / bodies[idB].mass;
        }
    }
    for(int i=0; i<nBodies; i++){
        bodies[i].velocity += deltaT*bodies[i].acceleration;
        bodies[i].position += deltaT*bodies[i].velocity;
        bodies[i].orbit.push_back(bodies[i].position);
    }
}

Bodies::~Bodies()
{
    delete[] bodies;
}
