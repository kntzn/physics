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
		virtual void update (std::vector <Body*> all_objects, double dt) = 0;

        virtual double getPotEnergy () = 0;
       	};

// Spring interaction pair
class SpringPair: protected Spring, public Pair
	{
	private:
		int p_left = -1, p_right = -1;
	public:
		SpringPair (std::vector <Body*> all_objects, double k, sf::Sprite* sprite,
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
		void update (std::vector <Body*> all_objects, double dt)
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

        double getPotEnergy ()
            { 
            return Spring::getPotEnergy ();
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

double pointToLineDist (Vectord point, Vectord lineLeft, Vectord lineRight)
    { 
    Vectord deltaLine = lineRight - lineLeft;

    if (deltaLine.x == 0.f)
        return fabs (point.x - lineLeft.x);
    
    double k_Line = deltaLine.y/deltaLine.x;
    double l_Line = lineLeft.y - lineLeft.x*k_Line;

    //   L =    |      ax       +     bx      +    c  | / sqrt (a^2     +     b^2)   
    return fabs (point.x*k_Line - point.y*1.f + l_Line) / sqrt (k_Line*k_Line + 1);
    }

// TODO: Materials propreties file load

class CollisionPair: public Pair
	{
	private:
		int p_left = -1, p_right = -1;

        double hardness = 10000000;
        double potEnergy = 0;

	public:
		CollisionPair (size_t left, size_t right): Pair (left, right)
			{
            
			}

		void update (std::vector <Body*> all_objects, double dt)
			{
            potEnergy = 0;

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
                        double closestEdgeToPointDistance = INFINITY;
                        size_t closestEdge = 0;
                        size_t N = left->nPoints ();

                        // Finding closest edge
                        for (size_t j = 0; j < N; j++)
                            {
                            double dist = pointToLineDist (right->getPointPos (i), left->getPointPos (j), left->getPointPos ((j+1)%N));

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

                        RestReaction *= (closestEdgeToPointDistance) * hardness;

                        right->applyForce (i, RestReaction, dt);
                        left->applyForceToVirtual (right->getPointPos (i), -RestReaction, dt);

                        potEnergy += (closestEdgeToPointDistance*closestEdgeToPointDistance*hardness/2);
                        }

                
				}
			}

		void draw (sf::RenderWindow &window, bool points = false)
			{
			}

        double getPotEnergy ()
            { 
            return potEnergy;
            }
	};


// TODO: add constant field gravity for any angle

class GravityPair: public Pair
    {
    private:
        double potEnergy = 0;

        enum type
            {
            const_field,
            var_field
            };

        int type = -1;
        Vectord acceleration = 0;


    public:
        GravityPair (std::vector <Body*> all_bodies, size_t right, size_t left): Pair (left, right)
            {
            type = var_field;

            Vectord deltaDist = all_bodies [right]->getPos ()-all_bodies [left]->getPos ();
            acceleration = deltaDist.dir ()*G*(all_bodies [right]->getMass ()*all_bodies [left]->getMass ())/
                pow (deltaDist.length (), 2);
            }
        GravityPair (std::vector <Body*> all_bodies, size_t body, Vectord const_acceleration): Pair (body, -1)
            {
            type = const_field;
            acceleration = const_acceleration;
            }

        void update (std::vector <Body*> all_bodies, double dt)
            {
            potEnergy = 0;

            switch (type)
                {
                case const_field:
                    {
                    all_bodies [id_left]->accelerate (acceleration, dt);

                    potEnergy = -all_bodies [id_left]->getPos ().y * 
                                acceleration.length () * all_bodies [id_left]->getMass ();
                    
                    break;
                    }
                case var_field:
                    {
                    Vectord deltaDist = all_bodies [id_right]->getPos ()-all_bodies [id_left]->getPos ();
                    acceleration = deltaDist.dir ()*G*(all_bodies [id_right]->getMass ()*all_bodies [id_left]->getMass ())/
                        pow (deltaDist.length (), 2);
                    all_bodies [id_left]->accelerate (-acceleration, dt);
                    all_bodies [id_right]->accelerate (acceleration, dt);


                    potEnergy = -G*(all_bodies [id_right]->getMass ()*all_bodies [id_left]->getMass ())/deltaDist.length ();
                    break;
                    }
                default:
                    break;
                }
            }

        double getPotEnergy ()
            {
            return potEnergy;
            }

        void draw (sf::RenderWindow &window, bool points = false)
            { 
            
            }
    };
