#include "Body.h"

Body::Body (Vector <float> Position, float Mass, Vector <float> Velocity, unsigned int nPoints, Vector <float> * pointsArray): Object (Position, Mass, Velocity)
	{
	// Creating array of points info
	n_points = nPoints;
	points = (Vector <float>*) calloc (n_points, sizeof (Vector <float>));

	// Calculating coordinates of mass center
	Vector <float> mass_center;
	for (size_t i = 0; i < n_points; i++)
		mass_center = mass_center + pointsArray [i];

	mass_center = mass_center / float (n_points);

	// Filling info array with angles and distances
	for (size_t i = 0; i < n_points; i++)
		{
		// Point to mass center radius vector
		Vector <float> deltaMassCenter = mass_center-pointsArray [i];

		// x coord - distance to center
		points [i].x = (deltaMassCenter).size ();
		// y coord - additional angle
		points [i].y = atan2 (deltaMassCenter.dir ().y, deltaMassCenter.dir ().x);
		}

	// Calculating total inertia moment of a body
	J = 0;
	for (size_t i = 0; i < n_points; i++)
		J += points [i].x * points [i].x * (mass/n_points) / 3;

	type = objectType::body;
	}
Body::~Body ()
	{
	free (points);
	}

void Body::applyForce (size_t point, Vector<float> Force, float dt)
	{
	if (0 <= point && point < n_points)
		{
		// Applying force directly to mass center:
		Object::addForce (Force, dt);

		// That part of the force that is able to rotate the body is equal to
		// the scalar product of the force vector by the unit vector of angle
		// (which is perpendicular to the radius vector from the point 
		// to which the force is applied to the center of mass of the body) 
		//
		// (see picture "body rotation" in folder "explanations")
		float activeForce = Force*Vector <float> (3.1416f/2+ angle+points [point].y);
		
		// Angular velocity increases proprtional to Torque 
		omega += (activeForce * points [point].x)/J;
		}
	}
void Body::update (float dt)
	{
	angle += omega*dt;
	Object::update (dt);
	}

Vector <float> Body::getPointPos (size_t point)
	{
	if (0 <= point && point < n_points)
		{
		// Calculating current total angle of point:
		Vector <float> deltaPos (points [point].y+angle);
		// Multiplying unit direction angle and distance from mass center
		deltaPos = deltaPos*points [point].x;
		// Adding position vector
		deltaPos = deltaPos + r;

		return deltaPos;
		}

	// In case of incorrect point id function returns mass center coordinates
	return r;
	}

void Body::draw (sf::RenderWindow & window)
	{
	// Drawing mass center point
	sf::CircleShape point (5);
	point.setOrigin (5, 5);
	point.setPosition (r.x, r.y);

	window.draw (point);

	for (size_t i = 0; i < n_points; i++)
		{
		point.setPosition (r.x, r.y);

			
		Vector <float> deltaPos (points [i].y+angle);
		deltaPos = deltaPos*points [i].x;
		point.move (deltaPos.toSf());
		window.draw (point);

		// Drawing line between point and mass center

		sf::Vertex line [2] = 
			{
			line [0] = sf::Vertex (r.toSf (), sf::Color::White),
			line [1] = sf::Vertex (point.getPosition (), sf::Color::White)
			};
		window.draw (line, 2, sf::LinesStrip);
		}
	}
