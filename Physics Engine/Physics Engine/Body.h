#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>

class Body: public Object
	{
	protected:
		// Vectors that contains points' distance from mass center (x) and additional angle of rotation (y)
		Vectorf * points = nullptr;
		size_t n_points = 0;

		float angle = 0;
		float omega = 0;
		float torq = 0;
		float J = 1;

	public:
		Body::Body (Vectorf Position, float Mass, Vectorf Velocity, unsigned int nPoints, Vectorf * pointsArray);
		~Body ();

		void applyForce (size_t point, Vectorf Force, float dt);
		void update (float dt);

		Vectorf getPointPos (size_t point);

		void draw (sf::RenderWindow &window);
		};

