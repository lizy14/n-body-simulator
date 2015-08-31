#include "bodies.h"
#include <QDebug>
#include <QMessageBox>

const double Bodies::G = 7000;
const double Bodies::k = 0.01;
const double Bodies::Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;


Bodies::Bodies(int nBodies_, double initialVelocity_, double deltaT_, int maxPointsInOrbit_)
    :
      nBodies(nBodies_),
      deltaT(deltaT_),
      maxPointsInOrbit(maxPointsInOrbit_),
      nPointsInOrbit(0),retry(true)
{
    bodies = new Body[nBodies];
    if(initialVelocity_<0)
        initialVelocity_ = nBodies*2;
    for(int i=0; i<nBodies; i++){
        double sin_ = sin(i/(double)nBodies * 2 * Pi);
        double cos_ = cos(i/(double)nBodies * 2 * Pi);
        bodies[i].position = QPointF(
                    sin_*100,
                    cos_*100
                    );
        bodies[i].velocity = QPointF(
                    cos_*initialVelocity_,
                    -sin_*initialVelocity_
                    );
    }
    return;
}



QPointF Bodies::gravity(int idA, int idB){
    if(idA==idB) throw("gravity calculation error");
    QPointF dx = bodies[idA].position - bodies[idB].position;
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



    bool newPoint=maxPointsInOrbit<0 || nPointsInOrbit<maxPointsInOrbit;
    if(newPoint)
        nPointsInOrbit++;

    for(int i=0; i<nBodies; i++){

        bodies[i].velocity += deltaT*bodies[i].acceleration;
        bodies[i].position += deltaT*bodies[i].velocity;

        if(!newPoint)
            bodies[i].orbit.removeFirst();
        bodies[i].orbit.push_back(bodies[i].position);
    }
}

Bodies::~Bodies()
{
    delete[] bodies;
}
