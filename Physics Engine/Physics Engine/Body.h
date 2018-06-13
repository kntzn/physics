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
		float angle = 0;
		// Angular speed;
		float omega = 0;
		// Inertia moment
		float J = 1;
		
		// Maximum distance from mass center (farthest point)
		float radius = 0;

	public:
		Body::Body (Vectord Position, float Mass, Vectord Velocity, unsigned int nPoints, Vectord * pointsArray);
		~Body ();

		void applyForce (int point, Vectord Force, float dt);
        void applyAccel (int point, Vectord Accel, float dt);

        void applyForceToVirtual (Vectord virtualPoint, Vectord Force, float dt);
        void accelerateVirtual   (Vectord virtualPoint, Vectord Accel, float dt);
		
        void update (float dt);

		Vectord getPointPos (int point);
		float getRadius ();
		size_t nPoints ();
        float getMass ();
        float getKinEnergy ();

		void draw (sf::RenderWindow &window);
		};

