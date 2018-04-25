#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Spring.h"
#include "Body.h"
#include "Ground.h"
#include <stdio.h>
#include <iostream>

int main ()
	{
	sf::Image img;
	img.loadFromFile ("spr.png");
	img.createMaskFromColor (sf::Color (0, 0, 255));
	sf::Texture txtr;
	txtr.loadFromImage (img);
	sf::Sprite spring_sprite;
	spring_sprite.setTexture (txtr);
	spring_sprite.setOrigin (sf::Vector2f (txtr.getSize ())/2.f);

	sf::Image img_gnd;
	img_gnd.loadFromFile ("ground.png");
	img_gnd.createMaskFromColor (sf::Color (0, 0, 255));
	sf::Texture ground_fill_txtr;
	ground_fill_txtr.loadFromImage (img_gnd);


	Vector <float> points_array [3] = 
		{
		Vector <float> (20, 20),
		Vector <float> (-80, 20),
		Vector <float> (-20, -40)
		};

	Body body (Vector <float> (400, 300), 10, Vector <float> (40, 0), 3, points_array);
	Body body2 (Vector <float> (400, 500), 10, Vector <float> (-40, 0), 3, points_array);
	Ground gnd (ground_fill_txtr, Vector <float> (800, 600), 3, points_array);

	Spring spr (&spring_sprite, body.getPos (), body2.getPos (), 10.0f);

	sf::RenderWindow window (sf::VideoMode (1600, 900), "");

	while (window.isOpen ())
		{
		spr.update (body.getPos (), body2.getPos ());

		body.addForce (spr.getForceLeft (), 0.016f);
		body2.addForce (spr.getForceRight (), 0.016f);
		
		body.update (0.016f);
		body2.update (0.016f);

		window.clear ();

		spr.draw (window);
		body.draw (window);
		body2.draw (window);
		gnd.draw (window);

		window.display ();
		}
	}