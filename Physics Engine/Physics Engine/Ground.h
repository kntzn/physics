#pragma once
#include "Body.h"
class Ground:
	public Body
	{
	private:
		sf::Texture ground_txtr;
	public:
		Ground::Ground (sf::Texture &ground_fill_txtr, Vector <float> Position, unsigned int nPoints, Vector <float> * pointsArray):
			Body (Position, INFINITY, Vector <float> (0, 0), nPoints, pointsArray)
			{
			ground_txtr = ground_fill_txtr;
			//ground_txtr.setRepeated (true);
			}
		~Ground ()
			{ 
			}

		void draw (sf::RenderWindow &window)
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
	};

