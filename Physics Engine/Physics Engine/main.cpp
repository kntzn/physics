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
	
	Vectord* points_array = Obj_Shape::truePolygon (4, 50, pi/4);

	std::vector <Body*> all_objects;
	std::vector <Pair*> interaction_pairs;

	all_objects.push_back (new Body (Vectord (500, 100), 1000, Vectord (0.f, 0.3f), 4, points_array));
    all_objects.push_back (new Body (Vectord (300, 0),   1000, Vectord (0.f, 0.3f), 4, points_array));

    all_objects.push_back (new Ground (ground_fill_txtr, Vectord (300, 600), 4, Obj_Shape::rectangle (Vectord (600, 50))));

    //all_objects.push_back (new Body (Vectord (600, 800), 1000, Vectord (0, 0), 4, points_array));
    
	//interaction_pairs.push_back (new SpringPair (all_objects, 0.04f, &spring_sprite, 0, 1, 2, 2));
	interaction_pairs.push_back (new CollisionPair (1, 0));
    interaction_pairs.push_back (new CollisionPair (0, 1));
	interaction_pairs.push_back (new CollisionPair (2, 0));
    interaction_pairs.push_back (new CollisionPair (0, 2));
    interaction_pairs.push_back (new CollisionPair (1, 2));
    interaction_pairs.push_back (new CollisionPair (2, 1));
    
    
	sf::RenderWindow window (sf::VideoMode (1600, 900), "");

	const float dt_c = 0.05f;
	sf::Clock timer;

    double minE = -INFINITY;
	
	while (window.isOpen ())
		{
		//float dt_c = timer.getElapsedTime ().asSeconds ()*100.f;
		timer.restart ();

        float Energy = 0.f;

        for (auto pair: interaction_pairs)
            {
            pair->update (all_objects, dt_c);
            Energy += pair->getPotEnergy ();
            }
		
        for (auto obj: all_objects)
            {
            obj->addForce (Vectord (0, 9.8f), dt_c);
            obj->update (dt_c);
            if (obj->getMass () != INFINITY)
                Energy += obj->getKinEnergy ();
            if (obj->getMass () != INFINITY)
                Energy -= obj->getMass ()*9.8f*obj->getPos ().y;
            }

        if (Energy > minE)
            minE = Energy;

		// --------- Graphics ---------
		window.clear ();

		for (auto obj: all_objects)
			obj->draw (window);
		
		for (auto pair: interaction_pairs)
			pair->draw (window);

        printf ("%lg\t\t(min: %lg)\n", Energy, minE);
		window.display ();

		}
	}