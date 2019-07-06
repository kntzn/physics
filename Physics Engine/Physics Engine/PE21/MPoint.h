#pragma once
#include "Vector.h"
#include <iostream>

class MPoint
    {
    protected:
        // Contains position (radius-vector, r)
        //          current velocity        (V)
        //          last acceleration       (a)
        //          mass                    (m)
        Vectord r, V, a;
        double m;

    public:
        MPoint (Vectord position,
                double mass,
                Vectord velocity = Vectord (0, 0));
        ~MPoint ();

        // Integrator
        void integrateEuler (double dt);

        // Setters
        void addForce (Vectord force);
        void accelerate (Vectord acceleration);

        // Getters
        Vectord getPos ();
        Vectord getVel ();
        double getMass ();

        double getKinEnergy ();
    };
