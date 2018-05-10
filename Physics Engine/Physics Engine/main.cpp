#include <SFML/Graphics.hpp>

#include "FileLoad.h"
#include "Object.h"
#include "Spring.h"
#include "Body.h"
#include "Ground.h"
#include "Shapes.h"
#include "Pairs.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>

int main ()
	{
	sf::Texture txtr = loadTextureWithMask ("spr.png");
	sf::Sprite spring_sprite;
	spring_sprite.setTexture (txtr);
	spring_sprite.setOrigin (sf::Vector2f (txtr.getSize ())/2.f);

	sf::Texture ground_fill_txtr = loadTextureWithMask ("ground.png");
	
	Vectorf* points_array = truePolygon (4, 50, pi/4);

	std::vector <Body*> all_objects;
	std::vector <Pair*> interaction_pairs;

	all_objects.push_back (new Body (Vectorf (300, 100), 1000, Vectorf (1, 0), 4, points_array));
	all_objects.push_back (new Body (Vectorf (400, 500), 1000, Vectorf (1, 1), 4, points_array));
	all_objects.push_back (new Ground (ground_fill_txtr, Vectorf (600, 600), 4, points_array));
	all_objects.push_back (new Body (Vectorf (600, 800), 1000, Vectorf (0, 0), 4, points_array));

	interaction_pairs.push_back (new SpringPair (all_objects, 0.04f, &spring_sprite, 0, 1, 2, 2));
	//interaction_pairs.push_back (new CollisionPair (2, 1));
	//interaction_pairs.push_back (new CollisionPair (2, 0));


	sf::RenderWindow window (sf::VideoMode (1600, 900), "");

	const float dt_c = 0.1f;
	
	while (window.isOpen ())
		{
		for (auto pair: interaction_pairs)
			pair->update (all_objects, dt_c);

		for (auto obj: all_objects)
			obj->update (dt_c);

		// --------- Graphics ---------
		window.clear ();

		for (auto obj: all_objects)
			obj->draw (window);
		
		for (auto pair: interaction_pairs)
			pair->draw (window);

		window.display ();
		}
	}