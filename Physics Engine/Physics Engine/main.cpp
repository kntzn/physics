#include <SFML/Graphics.hpp>

#include "FileLoad.h"
#include "Object.h"
#include "Spring.h"
#include "Body.h"
#include "Ground.h"
#include <stdio.h>
#include <iostream>

int main ()
	{
	sf::Texture txtr = loadTextureWithMask ("spr.png");
	sf::Sprite spring_sprite;
	spring_sprite.setTexture (txtr);
	spring_sprite.setOrigin (sf::Vector2f (txtr.getSize ())/2.f);

	sf::Texture ground_fill_txtr = loadTextureWithMask ("ground.png");


	Vectorf points_array [3] =
		{
		Vectorf (40, 40),
		Vectorf (-160, 40),
		Vectorf (-40, -80)
		};

	Body body (Vectorf (300, 100), 10000, Vectorf (5, 0), 3, points_array);
	Body body2 (Vectorf (400, 500), 10000, Vectorf (-5, 0), 3, points_array);
	Ground gnd (ground_fill_txtr, Vectorf (600, 600), 3, points_array);

	Spring spr (&spring_sprite, body.getPos (), body2.getPos (), 2.0f);

	sf::RenderWindow window (sf::VideoMode (1600, 900), "");

	const float dt_c = 0.016f;
	sf::Clock timer;

	while (window.isOpen ())
		{
		float dt = 0;
		if (timer.getElapsedTime ().asSeconds ()*40.f > dt_c)
			{
			timer.restart ();
			dt = dt_c;
			}

		spr.update (body.getPos (), body2.getPointPos (1));

		body.addForce (spr.getForceLeft (), dt);
		body2.applyForce (1, spr.getForceRight (), dt);
		
		body.update (dt);
		body2.update (dt);

		// --------- Graphics ---------
		window.clear ();

		spr.draw (window);
		body.draw (window);
		body2.draw (window);
		gnd.draw (window);
		
		window.display ();
		}
	}