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
#include "Graph.h"


int main ()
	{
    // -------- GRAPHICS -------- 
    sf::Texture txtr = loadTextureWithMask ("spr.png");
	sf::Sprite spring_sprite;
	spring_sprite.setTexture (txtr);
	spring_sprite.setOrigin (sf::Vector2f (txtr.getSize ())/2.f);

	sf::Texture ground_fill_txtr = loadTextureWithMask ("ground.png");
	
    // - OBJECTS AND INTERACTIONS - 
	Vectord* points_array = Obj_Shape::truePolygon (4, 0.5, pi/4);

	std::vector <Body*> all_objects;
	std::vector <Pair*> interaction_pairs;

    all_objects.push_back (new Ground (ground_fill_txtr, Vectord (1, 1), 4, Obj_Shape::rectangle (Vectord (0.5, 0.5))));
    all_objects.push_back (new Ground (ground_fill_txtr, Vectord (5, 1), 4, Obj_Shape::rectangle (Vectord (0.5, 0.5))));
    all_objects.push_back (new Body (Vectord (5, 4), 10, Vectord (0, -0.1), 4, points_array));
    
    //all_objects.push_back (new Body (Vectord (300, 400),   1000, Vectord (0, 0), 4, points_array));
    //all_objects.push_back (new Body (Vectord (600, 800), 1000, Vectord (0, 0), 4, points_array));
    
    interaction_pairs.push_back (new SpringPair (all_objects, 100, &spring_sprite, 2, 1, -1, -1));
    interaction_pairs.push_back (new GravityPair (all_objects, 2, Vectord (0, g)));


    // - CAMERA, TIME AND WINDOW - 
    // Window
    sf::RenderWindow window (sf::VideoMode (1600, 900), "");
    sf::RenderWindow graph_window (sf::VideoMode (900, 900), "");

    // Camera
    Camera cam (sf::FloatRect (0, 0, 16, 9));
    Camera cam_for_grpah_widow (sf::FloatRect (0, 0, 900, 900));
    bool transitionEnded = true;
    float deltaZoom = 0;
    sf::Vector2i mousePosBegin = sf::Mouse::getPosition (window);
    sf::Vector2f camCenterPosBegin = cam.getCenter ();

    // Time
	const double dt_c = 0.001f;
    sf::Clock timer;
    
    // --------- ENERGY --------- 
    double initialPotentialEnergy = 0;
    double initialKineticEnergy = 0;

    // Calculating initial potential and kinetic energy
    for (auto pair: interaction_pairs)
        {
        pair->update (all_objects, dt_c);
        initialPotentialEnergy += pair->getPotEnergy ();
        }
        
    for (auto obj: all_objects)
        {
        if (obj->getMass () != INFINITY)
            initialKineticEnergy += obj->getKinEnergy ();
        }

    // Graphs
    Graph graph (900, sf::Color::Magenta);
    Graph graph_y (900, sf::Color::Green);
    

    Spring spr (&spring_sprite, Vectord (0, 0), Vectord (100, 100), 1);
    //spr.scale_const = 1;


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
                    
                    mousePosBegin = sf::Mouse::getPosition (window);
                    camCenterPosBegin = cam.getCenter ();
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
        double KinEnergy = 0;
        double PotEnergy = 0;

        // Updaitng interactions
        for (auto pair: interaction_pairs)
            {
            pair->update (all_objects, dt_c);
            PotEnergy += pair->getPotEnergy ();
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
        double EnergyLoss = (deltaKinEnergy + deltaPotEnergy);
        double EnergyLossPerc = (deltaKinEnergy + deltaPotEnergy)/(KinEnergy + deltaPotEnergy)*100;

        graph.addPoint (EnergyLoss);
        graph_y.addPoint (-all_objects [2]->getPos ().y);

        

        // --------- Graphics ---------
		// Camera
        cam.scope (deltaZoom);
        window.setView (cam);
        
        if (!transitionEnded)
            {
            cam.setCenter (camCenterPosBegin + sf::Vector2f (window.mapPixelToCoords (mousePosBegin) - window.mapPixelToCoords (sf::Mouse::getPosition (window))));
            }

        // Drawing everything
        window.clear ();
        graph_window.clear ();
        
        for (auto obj: all_objects)
			obj->draw (window);
		
		for (auto pair: interaction_pairs)
			pair->draw (window);

        
        graph.draw (graph_window, cam_for_grpah_widow);
        graph_y.draw (graph_window, cam_for_grpah_widow);
        
        // Output:
        if (EnergyLoss > 0)
            printf ("Energy Loss:  %lg%\n", EnergyLoss);
        else
            printf ("Additional E: %lg%\n", -EnergyLoss);

        //printf ("potential E: %lg %lg\n", initialPotentialEnergy, deltaPotEnergy);


        window.display ();
        graph_window.display ();
		}
	}