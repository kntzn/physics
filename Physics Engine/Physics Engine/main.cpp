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
#include "Camera.h"


int main ()
	{
    // -------- GRAPHICS -------- 
    sf::Texture txtr = loadTextureWithMask ("spr.png");
	sf::Sprite spring_sprite;
	spring_sprite.setTexture (txtr);
	spring_sprite.setOrigin (sf::Vector2f (txtr.getSize ())/2.f);

	sf::Texture ground_fill_txtr = loadTextureWithMask ("ground.png");
	
    // - OBJECTS AND INTERACTIONS - 
	Vectord* points_array = Obj_Shape::truePolygon (4, 50, pi/4);

	std::vector <Body*> all_objects;
	std::vector <Pair*> interaction_pairs;

    all_objects.push_back (new Ground (ground_fill_txtr, Vectord (100, 100), 4, Obj_Shape::rectangle (Vectord (50, 50))));
    all_objects.push_back (new Ground (ground_fill_txtr, Vectord (500, 100), 4, Obj_Shape::rectangle (Vectord (50, 50))));
    all_objects.push_back (new Body (Vectord (530, 400), 1, Vectord (60, 0), 4, points_array));
    
    //all_objects.push_back (new Body (Vectord (300, 400),   1000, Vectord (0, 0), 4, points_array));
    //all_objects.push_back (new Body (Vectord (600, 800), 1000, Vectord (0, 0), 4, points_array));
    
    interaction_pairs.push_back (new SpringPair (all_objects, 10, &spring_sprite, 2, 1, 0, 0));
    interaction_pairs.push_back (new GravityPair (all_objects, 2, Vectord (0, g)));


    // - CAMERA, TIME AND WINDOW - 
    // Window
    sf::RenderWindow window (sf::VideoMode (1600, 900), "");

    // Camera
    Camera cam (sf::FloatRect (0, 0, 160, 90));
    bool transitionEnded = true;
    float deltaZoom = 0;
    sf::Vector2i mousePosOffset = sf::Mouse::getPosition (window) - 
                                  sf::Vector2i (cam.getCenter ());
    
    // Time
	const double dt_c = 0.01f;
    sf::Clock timer;
    
    // --------- ENERGY --------- 
    double initialPotentialEnergy = 0;
    double initialKineticEnergy = 0;

    // Calculating initial potential and kinetic energy
    for (auto pair: interaction_pairs)
        initialPotentialEnergy += pair->getPotEnergy ();
    for (auto obj: all_objects)
        {
        if (obj->getMass () != INFINITY)
            initialKineticEnergy += obj->getKinEnergy ();
        }

    // ------- MAIN CYCLE ------- 
	while (window.isOpen ())
		{
		//double dt_c = timer.getElapsedTime ().asSeconds ();
		timer.restart ();

        // Events
        deltaZoom = 0;
        sf::Event event;
        while (window.pollEvent (event))
            {
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == sf::Mouse::Left)
                    {
                    transitionEnded = false;
                    
                    mousePosOffset = sf::Mouse::getPosition (window) +
                                     sf::Vector2i (cam.getCenter ());

                    }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.key.code == sf::Mouse::Left)
                    transitionEnded = true;


            if (event.type == sf::Event::Closed)
                window.close ();    

            if (event.type == sf::Event::MouseWheelMoved)
                deltaZoom = float (event.mouseWheel.delta)/20.f;
            }

        // Energy variables
        double KinEnergy = 0.f;
        double PotEnergy = 0.f;

        // Updaitng interactions
        for (auto pair: interaction_pairs)
            {
            PotEnergy += pair->getPotEnergy ();
            pair->update (all_objects, dt_c);
            }
		
        // Updating objects
        for (auto obj: all_objects)
            {
            if (obj->getMass () != INFINITY)
                KinEnergy += obj->getKinEnergy ();

            obj->update (dt_c);
            }

        // Energy calculations:
        double deltaKinEnergy = KinEnergy - initialKineticEnergy;
        double deltaPotEnergy = PotEnergy - initialPotentialEnergy;
        double EnergyLoss = (deltaKinEnergy + deltaPotEnergy)/(KinEnergy + deltaPotEnergy)*100;

        // --------- Graphics ---------
		// Camera
        cam.scope (deltaZoom);
        window.setView (cam);
        
        if (!transitionEnded)
            {
            cam.setCenter (sf::Vector2f (mousePosOffset - sf::Mouse::getPosition (window)));
            
            printf ("x  %f\n, y %f\n", cam.getCenter().x, cam.getCenter().y);
            }

        // Drawing everything
        window.clear ();
        
        for (auto obj: all_objects)
			obj->draw (window);
		
		for (auto pair: interaction_pairs)
			pair->draw (window);

        // Output:
        if (EnergyLoss > 0)
            printf ("Energy Loss:  %lg%3%%\n", EnergyLoss);
        else
            printf ("Additional E: %lg%3%%\n", -EnergyLoss);

        window.display ();

		}
	}

