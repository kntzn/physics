#include "Spring.h"
#include "Constants.h"

Spring::Spring (sf::Sprite* spring_spr, Vector<float> begin, Vector<float> end, float k)
	{
	// physics
	hardness = k;
	max_dist = min_dist = init_dist = (begin-end).size();

	right = begin;
	left = end;

	// graphics
	spring_sprite = *spring_spr;
	
	scale_const = init_dist/(spring_spr->getOrigin ().x*2);
	spring_sprite.scale (scale_const, 1);
	}

Spring::~Spring ()
	{
	
	}

// Returns force applied to rights point
Vector<float> Spring::getForceRight ()
	{
	return Vector<float> (-Force);
	}
// Returns force applied to left point
Vector<float> Spring::getForceLeft ()
	{
	return Vector<float> (Force);
	}

void Spring::update (Vector <float> begin, Vector <float> end)
	{
	// Transforming difference between new (updated) positions of the ends into current size of the spring
	curr_dist = (begin-end).size ();

	// Updating minimal and maximal sizes of the spring to use them in further calculations
	if (curr_dist > max_dist)
		max_dist = curr_dist;
	if (curr_dist < min_dist)
		min_dist = curr_dist;

	// Calculating difference between initial size of the spring and its current size
	//    dx   =     x     -    x0
	delta_dist = curr_dist - init_dist;

	// Updating positions of spring ends to use them in further calculations
	right = begin;
	left = end;
	
	// Calculation of the tension force of the spring
	Force = (end-begin).dir();
	Force = Force*delta_dist; 
	Force = Force*hardness;
	}

void Spring::draw (sf::RenderWindow & window, bool points)
	{
	// ------- Position and rotation -------
	// Rotating spring sprite
	spring_sprite.setRotation (atan2 ((right - left).y, (right - left).x)*toDeg);

	// Calculating radius vector of middle point between ends
	// and converting Vector <float> to sf::Vector2f
	spring_sprite.setPosition ((right + left).toSf ()/2.f);

	// Scaling sprite by width axis according to deformation
	spring_sprite.setScale (scale_const*(curr_dist/init_dist), 1);

	// ------- Colors ------- 
	// Setting color according to deformation (Red means stretched, blue means compressed)
	// if (spring is stretched) calculating spring color according to max size ever reached
	if (delta_dist > 0)
		spring_sprite.setColor (sf::Color (127 + delta_dist/(init_dist - max_dist)*127, 0, 127 - delta_dist/(init_dist - max_dist)*127));
	// Otherwise calculating spring color according to min size ever reached
	else
		spring_sprite.setColor (sf::Color (127 - delta_dist/(init_dist - min_dist)*127, 0, 127 + delta_dist/(init_dist - min_dist)*127));

	// Drawing sprite
	window.draw (spring_sprite);

	// ------- Points ------- 
	// if points are necessary
	if (points)
		{
		// Creating circle object with radius bounded with scale 
		sf::CircleShape cs (5*scale_const);

		// Setting origin of points to center of the circle
		cs.setOrigin (cs.getRadius()/2.f, cs.getRadius ()/2.f);

		// Drawing right one (converted to sf::Vector2f)
		cs.setPosition (right.toSf ());
		window.draw (cs);
		
		// Drawing left one (also converted to sf::Vector2f)
		cs.setPosition (left.toSf ());
		window.draw (cs);
		}
	}