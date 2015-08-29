#ifndef BODIES_H
#define BODIES_H

#include <QPointF>
#include <QVector>
class Body
{
public:
    double mass;
    QPointF position, velocity, acceleration;
    QVector<QPointF> orbit;
    Body():mass(1){}
};

class Bodies
{
private:
    const static double G;
    const static double k;
    static double deltaT;
public:
    int nBodies;

public:
    Bodies(int nBodies_);
    Bodies(){}
    ~Bodies();
    Body* bodies;
    void advance();
private:
    QPointF gravity(int idA, int idB);
};

#endif // BODIES_H
