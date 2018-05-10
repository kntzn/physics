#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Spring.h"
#include <vector>

// Objects Pair Class
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
		virtual void update (std::vector <Body*> all_objects, float dt) = 0;
	};

// Spring interaction pair
class SpringPair: protected Spring, public Pair
	{
	private:
		int p_left = -1, p_right = -1;
	public:
		SpringPair (std::vector <Body*> all_objects, float k, sf::Sprite* sprite,
			size_t left, size_t right, int point_left = -1, int point_right = -1):
			// Inheritating from Spring class (by getting points coords info)
			// In case point_left or point_right is equal to -1, getPointPos returns mass center
			Spring (sprite, 
				all_objects [left]->getPointPos (point_left), 
				all_objects [right]->getPointPos (point_right), k),
			// Inheritating from Pair class
			Pair (left, right)
			{
			p_left = point_left;
			p_right = point_right;
			}

		// Spring and objects updae
		void update (std::vector <Body*> all_objects, float dt)
			{
			// Updates spring
			Spring::update (all_objects [id_left]->getPointPos (p_left), 
				all_objects [id_right]->getPointPos (p_right));

			// Applies force to the body
			all_objects [id_left]->applyForce (p_left, Spring::getForceLeft (), dt);
			all_objects [id_right]->applyForce (p_right, Spring::getForceRight (), dt);
			}

		// Just drawing the spring
		void draw (sf::RenderWindow &window, bool points = false)
			{ 
			Spring::draw (window, points);
			}
	};


int inPoly (Body* body, Vectorf point)
	{
	bool inside = false;
	int j = body->nPoints () - 1;
	for (int i = 0; i < body->nPoints (); i++)
		{
		if ((body->getPointPos (i).x < point.y && body->getPointPos (j).y >= point.y || 
			 body->getPointPos (j).y < point.y && body->getPointPos (i).y >= point.y) &&

			(body->getPointPos (i).x + (point.y - body->getPointPos (i).y) /
			(body->getPointPos (j).y - body->getPointPos (i).y) *
			(body->getPointPos (j).x - body->getPointPos (i).x) < point.x) )
			inside = !inside;
	
		j = i;
		}

	return inside;
	}

class CollisionPair: public Pair
	{
	private:
		int p_left = -1, p_right = -1;
	public:
		CollisionPair (size_t left, size_t right): Pair (left, right)
			{
			}

		void update (std::vector <Body*> all_objects, float dt)
			{
			Body* left  = all_objects [id_left];
			Body* right = all_objects [id_right];
			
			// if objects are close enough
			if ((left->getPos () - right->getPos ()).length () < left->getRadius () + right->getRadius ())
				{
				for (size_t i = 0; i < right->nPoints (); i++)
					if (inPoly (left, right->getPointPos (i)))
						{
						
						}
				}
			}

		void draw (sf::RenderWindow &window, bool points = false)
			{
			}
	};