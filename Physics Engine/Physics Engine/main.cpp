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

	all_objects.push_back (new Body (Vectord (500, 500), 1000, Vectord (0, 0), 4, points_array));
    all_objects.push_back (new Body (Vectord (300, 400),   1000, Vectord (0, 0), 4, points_array));

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

	const float dt_c = 0.0001f;
	sf::Clock timer;

    float initialPotentialEnergy = 0;
    float initialKineticEnergy = 0;

    for (auto pair: interaction_pairs)
        initialPotentialEnergy += pair->getPotEnergy ();
    for (auto obj: all_objects)
        {
        if (obj->getMass () != INFINITY)
            initialPotentialEnergy -= obj->getMass ()*g*obj->getPos ().y;
        
        if (obj->getMass () != INFINITY)
            initialKineticEnergy += obj->getKinEnergy ();
        }

	while (window.isOpen ())
		{
		//float dt_c = timer.getElapsedTime ().asSeconds ()*100.f;
		timer.restart ();

        float KinEnergy = 0.f;
        float PotEnergy = 0.f;

        for (auto pair: interaction_pairs)
            {
            PotEnergy += pair->getPotEnergy ();
            pair->update (all_objects, dt_c);
            }
		
        for (auto obj: all_objects)
            {
            if (obj->getMass () != INFINITY)
                KinEnergy += obj->getKinEnergy ();


            if (obj->getMass () != INFINITY)
                PotEnergy -= obj->getMass ()*g*obj->getPos ().y;

            
            obj->accelerate (Vectord (0, g), dt_c);
            obj->update (dt_c);
            }

        for (auto pair: interaction_pairs)
            {
            //PotEnergy += pair->getPotEnergy ();
            }

        // --------- Graphics ---------
		window.clear ();

		for (auto obj: all_objects)
			obj->draw (window);
		
		for (auto pair: interaction_pairs)
			pair->draw (window);
        
        printf ("Pot: %lg J \t\tKin: %lf J \t\t(dKin: %lf J)\t(dPot: %lg J)\t\tloss: %lg\n", PotEnergy, KinEnergy, 
                                                        -initialKineticEnergy + KinEnergy, 
                                                        -initialPotentialEnergy + PotEnergy,
                                                        initialKineticEnergy + initialPotentialEnergy - KinEnergy - PotEnergy);
		window.display ();

		}
	}