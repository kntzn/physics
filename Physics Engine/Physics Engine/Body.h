#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>

class Body: public Object
	{
	protected:
		// Vectors that contains points' distance from mass center (x) and additional angle of rotation (y)
		Vectord * points = nullptr;
		// Number of points
		size_t n_points = 0;

		// Angle of the body
		double angle = 0;
		// Angular speed;
		double omega = 0;
		// Inertia moment
		double J = 1;
		
		// Maximum distance from mass center (farthest point)
		double radius = 0;

	public:
		Body::Body (Vectord Position, double Mass, Vectord Velocity, 
                    unsigned int nPoints, Vectord * pointsArray);
		~Body ();

		void applyForce (int point, Vectord Force, double dt);
        void applyAccel (int point, Vectord Accel, double dt);

        void applyForceToVirtual (Vectord virtualPoint, Vectord Force, double dt);
        void accelerateVirtual   (Vectord virtualPoint, Vectord Accel, double dt);
		
        void update (double dt);

		Vectord getPointPos (int point);
		double getRadius ();
		size_t nPoints ();
        double getMass ();
        double getKinEnergy ();

		void draw (sf::RenderWindow &window);
		};

