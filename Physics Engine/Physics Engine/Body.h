#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>

class Body:
	public Object
	{
	private:
		// Vectors that contains points' distance from mass center (x) and additional angle of rotation (y)
		Vector <float> * points = nullptr;
		size_t n_points = 0;

		float angle = 0;
		float omega = 0;
		float torq = 0;
		float J = 1;

	public:
		Body::Body (Vector <float> Position, float Mass, Vector <float> Velocity, unsigned int nPoints, Vector <float> * pointsArray);
		~Body ();

		void applyForce (size_t point, Vector <float> Force, float dt);
		void update (float dt);

		Vector <float> getPointPos (size_t point);

		void draw (sf::RenderWindow &window);
		};

