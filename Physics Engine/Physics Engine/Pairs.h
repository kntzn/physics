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

        virtual float getPotEnergy () = 0;
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

bool inPoly (Body*body, Vectord pos)
	{
	bool in = false;
	for (int i = 0, j = body->nPoints () - 1; i < body->nPoints (); i++)
		{
		Vectord left  = body->getPointPos (j);
		Vectord right = body->getPointPos (i);

		if (((right.y < left.y) && (right.y <= pos.y) && (pos.y <=left.y) &&
			((left.y - right.y) * (pos.x - right.x) > (left.x - right.x) * (pos.y - right.y))) ||
			((right.y > left.y) && (left.y <= pos.y) && (pos.y <= right.y) &&
			((left.y - right.y) * (pos.x - right.x) < (left.x - right.x) * (pos.y - right.y))))
			in = !in;

		j = i;
		}
	return in;
	}

float pointToLineDist (Vectord point, Vectord lineLeft, Vectord lineRight)
    { 
    Vectord deltaLine = lineRight - lineLeft;

    if (deltaLine.x == 0.f)
        return fabs (point.x - lineLeft.x);
    
    float k_Line = deltaLine.y/deltaLine.x;
    float l_Line = lineLeft.y - lineLeft.x*k_Line;

    //       L =      |      ax       +     bx      +    c  | / sqrt (a^2     +     b^2)
    float dist = fabs (point.x*k_Line - point.y*1.f + l_Line) / sqrt (k_Line*k_Line + 1);

    return dist;
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
					// If (point is inside other body)
					if (inPoly (left, right->getPointPos (i)))
						{
						// ------Repulsion------
                        float closestEdgeToPointDistance = INFINITY;
                        size_t closestEdge = 0;
                        size_t N = left->nPoints ();

                        // Finding closest edge
                        for (size_t j = 0; j < N; j++)
                            {
                            float dist = pointToLineDist (right->getPointPos (i), left->getPointPos (j), left->getPointPos ((j+1)%N));

                            if (dist < closestEdgeToPointDistance)
                                {
                                closestEdgeToPointDistance = dist;
                                closestEdge = j;
                                }
                            }

                        Vectord RestReaction (left->getPointPos(closestEdge) - left->getPointPos((closestEdge+1)%N));
                        // Rotating vector 90 degrees CCW (because points of the body are in CW positions)
                        RestReaction = Vectord (-RestReaction.y, RestReaction.x);
                        // N =               dir           *            dx              *
                        RestReaction = RestReaction.dir ();

                        RestReaction *= (closestEdgeToPointDistance) * 10.f;

                        right->applyForce (i, RestReaction, dt);
                        left->applyForceToVirtual (right->getPointPos (i), -RestReaction, dt);
                        }

                
				}
			}

		void draw (sf::RenderWindow &window, bool points = false)
			{
			}

        float getPotEnergy ()
            { 
            return 0.f;
            }
	};