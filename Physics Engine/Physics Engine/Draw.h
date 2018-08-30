#pragma once
#include <SFML\Graphics.hpp>
#include "Vector.h"
#include "Body.h"

namespace Draw
	{
	void body (sf::RenderWindow & window, Body* b)
		{
		// Drawing mass center point
		sf::CircleShape point (b->getRadius ()/5);
		point.setOrigin (point.getRadius (), point.getRadius ());
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
		convex.setOutlineThickness (b->getRadius()/200);

		for (size_t i = 0; i < b->nPoints (); i++)
			convex.setPoint (i, b->getPointPos (i).toSf ());
			
		window.draw (convex);
		}
	}