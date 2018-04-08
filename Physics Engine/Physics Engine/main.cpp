#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Spring.h"
#include <stdio.h>
#include <iostream>

int main ()
	{
	sf::Texture txtr;
	txtr.loadFromFile ("spr.png");
	sf::Sprite spring_sprite;
	spring_sprite.setTexture (txtr);
	spring_sprite.setOrigin (sf::Vector2f (txtr.getSize ())/2.f);

	Spring spr1 (&spring_sprite, Vector <float> (200, 200), Vector <float> (400, 200), 1000);
	Object left  (Vector <float> (200, 200), 1000, Vector <float> (10, 0));
	Object right (Vector <float> (400, 200), 1000, Vector <float> (0, 3));

	sf::RenderWindow window (sf::VideoMode (1600, 900), "");

	while (window.isOpen ())
		{
		spr1.update (left.getPos(), right.getPos());
		
		left.addForce (spr1.getForceLeft (), 1/60.f);
		right.addForce (spr1.getForceRight (), 1/60.f);
		left.update (1/60.f);
		right.update (1/60.f);

		window.clear ();
		spr1.draw (window, true);
		window.display ();
		}

	system ("pause");
	}