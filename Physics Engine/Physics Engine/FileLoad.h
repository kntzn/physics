#pragma once
#include <SFML/Graphics.hpp>

sf::Texture loadTextureWithMask (char filename [], sf::Color mask = sf::Color (0, 0, 255))
	{ 
	sf::Image img;
	sf::Texture result;
	if (img.loadFromFile (filename))
		{
		img.createMaskFromColor (mask);
		result.loadFromImage (img);
		}
	else
		printf ("Failed to load texture\n");

	return result;
	}