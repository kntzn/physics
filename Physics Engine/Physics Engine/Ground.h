#pragma once
#include "Body.h"
class Ground:
	public Body
	{
	private:
		sf::Texture ground_txtr;
	public:
		Ground::Ground (sf::Texture &ground_fill_txtr, Vector <float> Position, unsigned int nPoints, Vector <float> * pointsArray);
		~Ground ();

		void draw (sf::RenderWindow &window);
	};

