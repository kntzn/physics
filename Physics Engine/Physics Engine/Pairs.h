#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Spring.h"
#include <vector>

class Pair
	{
	protected:
		int id_left = -1, id_right = -1;
		Pair (size_t left, size_t right)
			{ 
			id_left = left;
			id_right = right;
			}

	public:
		virtual void draw (sf::RenderWindow & window, bool points = false) = 0;
		virtual void update (std::vector <Object*> all_objects, float dt) = 0;
	};

class SpringPair: protected Spring, public Pair
	{
	public:
		SpringPair (size_t left, size_t right, std::vector <Object*> all_objects, float k, sf::Sprite* sprite):
			Spring (sprite, all_objects [left]->getPos (), all_objects [right]->getPos (), k),
			Pair (left, right)
			{

			}

		void update (std::vector <Object*> all_objects, float dt)
			{
			Spring::update (all_objects [id_left]->getPos (), all_objects [id_right]->getPos ());

			all_objects [id_left]->addForce (Spring::getForceLeft (), dt);
			all_objects [id_right]->addForce (Spring::getForceRight (), dt);
			}

		void draw (sf::RenderWindow &window, bool points = false)
			{ 
			Spring::draw (window, points);
			}
	};