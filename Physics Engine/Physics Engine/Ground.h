#pragma once
#include "Body.h"
class Ground: public Body
	{
	private:
		sf::Texture ground_txtr;
	public:
		Ground::Ground (sf::Texture ground_fill_txtr, Vectorf Position, unsigned int nPoints, Vectorf * pointsArray);
		~Ground ();

		void draw (sf::RenderWindow &window);
	};

