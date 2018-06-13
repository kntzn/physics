#pragma once
#include <SFML\Graphics.hpp>
#include "Vector.h"
#include "Body.h"

namespace Draw
	{
	void body (sf::RenderWindow & window, Body* b)
		{
		// Drawing mass center point
		sf::CircleShape point (5);
		point.setOrigin (5, 5);
		point.setPosition (b->getPos().toSf ());

		window.draw (point);

		for (size_t i = 0; i < b->nPoints (); i++)
			{
			point.setPosition (b->getPointPos (i).toSf ());
			window.draw (point);

			// Drawing line between point and mass center
			sf::Vertex line [] =
				{
				sf::Vertex (b->getPointPos ((i+1)%b->nPoints ()).toSf (), sf::Color::White),
				sf::Vertex (b->getPointPos (i).toSf (), sf::Color::White),
				sf::Vertex (b->getPos ().toSf(), sf::Color::White)
				};

			window.draw (line, 3, sf::PrimitiveType::Lines);
			window.draw (line, 3, sf::PrimitiveType::LineStrip);
			}
		}

	void ground (sf::RenderWindow & window, Body* b)
		{ 
		sf::ConvexShape convex (b->nPoints ());
		convex.setOutlineThickness (2);

		for (size_t i = 0; i < b->nPoints (); i++)
			convex.setPoint (i, b->getPointPos (i).toSf ());
			
		window.draw (convex);
		}
	}