#include "MPoint.h"

MPoint::MPoint (Vectord position,
                double mass,
                Vectord velocity):
    r (position),
    m (mass),
    V (velocity)
    {
    }
MPoint::~MPoint ()
    {
    }

// Integrator
void MPoint::integrateEuler (double dt)
    {
    V += Vectord (a * dt);
    r += Vectord (V * dt);

    a = Vectord (0, 0);
    }

// Setters
void MPoint::addForce (Vectord force)
    {
    a += force / m;
    }
void MPoint::accelerate (Vectord acceleration)
    {
    a += acceleration;
    }

// Getters
Vectord MPoint::getPos ()
    {
    return r;
    }
Vectord MPoint::getVel ()
    {
    return V;
    }
double MPoint::getMass ()
    {
    return m;
    }

double MPoint::getKinEnergy ()
    {
    // E     =     ( V^2 ) * m  / 2
    return double ((V * V) * m) / 2.0;
    }
