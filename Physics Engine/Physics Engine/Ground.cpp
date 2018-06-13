#include "Ground.h"



Ground::Ground (sf::Texture ground_fill_txtr, Vectord Position, unsigned int nPoints, Vectord * pointsArray):
	Body (Position, INFINITY, Vectord (0, 0), nPoints, pointsArray)
	{
	ground_txtr = ground_fill_txtr;
	
	type = objectType::ground;
	}


Ground::~Ground ()
	{
	}