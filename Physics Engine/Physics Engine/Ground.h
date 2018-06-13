#pragma once
#include "Body.h"
class Ground: public Body
	{
	private:
		sf::Texture ground_txtr;
	public:
		Ground::Ground (sf::Texture ground_fill_txtr, Vectord Position, unsigned int nPoints, Vectord * pointsArray);
		~Ground ();

	};

