#ifndef BODIES_H
#define BODIES_H

#include <QPointF>
#include <QList>
class Body
{
public:
    double mass;
    QPointF position, velocity, acceleration;
    QList<QPointF> orbit;
    Body():mass(1){}
};

class Bodies
{
private:
    const static double G;
    const static double k;
    const static double Pi;
public:
    double deltaT;
    int maxPointsInOrbit;
public:
    int nBodies;

public:
    Bodies(int nBodies_, double initialVelocity_ = -1, double deltaT_ = .5, int maxPointsInOrbit_=10000);
    Bodies(){}
    ~Bodies();
    Body* bodies;
    void advance();
private:
    QPointF gravity(int idA, int idB);
};

#endif // BODIES_H
