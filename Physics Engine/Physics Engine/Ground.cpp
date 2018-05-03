#include "Ground.h"



Ground::Ground (sf::Texture &ground_fill_txtr, Vectorf Position, unsigned int nPoints, Vectorf * pointsArray):
	Body (Position, INFINITY, Vectorf (0, 0), nPoints, pointsArray)
	{
	ground_txtr = ground_fill_txtr;
	
	type = objectType::ground;
	}


Ground::~Ground ()
	{
	}

void Ground::draw (sf::RenderWindow & window)
	{
	sf::ConvexShape convex (n_points);
	convex.setTexture (&ground_txtr);
	convex.setOutlineThickness (2);

	for (size_t i = 0; i < n_points; i++)
		{
		Vectorf deltaPos (points [i].y+angle);
		deltaPos = deltaPos*points [i].x;

		convex.setPoint (i, r.toSf ()+ deltaPos.toSf ());
		}

	window.draw (convex);
	}
