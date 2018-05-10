#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>

class Body: public Object
	{
	protected:
		// Vectors that contains points' distance from mass center (x) and additional angle of rotation (y)
		Vectorf * points = nullptr;
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
		Body::Body (Vectorf Position, float Mass, Vectorf Velocity, unsigned int nPoints, Vectorf * pointsArray);
		~Body ();

		void applyForce (int point, Vectorf Force, float dt);
		void applyForceToVirtual (Vectorf virtualPoint, Vectorf Force, float dt);
		void update (float dt);

		Vectorf getPointPos (int point);
		float getRadius ();
		size_t nPoints ();

		void draw (sf::RenderWindow &window);
		};

