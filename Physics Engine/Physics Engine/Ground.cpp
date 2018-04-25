#include "Ground.h"


void Ground::draw (sf::RenderWindow & window)
	{
	sf::ConvexShape convex (n_points);
	convex.setTexture (&ground_txtr);
	convex.setOutlineThickness (2);

	for (size_t i = 0; i < n_points; i++)
		{
		Vector <float> deltaPos (points [i].y+angle);
		deltaPos = deltaPos*points [i].x;

		convex.setPoint (i, r.toSf ()+ deltaPos.toSf ());
		}

	window.draw (convex);
	}
