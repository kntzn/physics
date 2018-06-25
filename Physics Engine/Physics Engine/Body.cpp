#include "Body.h"
#include "Constants.h"
#include "Draw.h"

Body::Body (Vectord Position, double Mass, Vectord Velocity, 
	        unsigned int nPoints, Vectord * pointsArray):
	Object (Position, Mass, Velocity)
	{
	type = objectType::body;

	// Creating array of points coords
	n_points = nPoints;
	points = (Vectord*) calloc (n_points, sizeof (Vectord));
	if (points == nullptr)
		printf ("Failed to create array of points\n");

	// Calculating coordinates of mass center
	Vectord mass_center;
	for (size_t i = 0; i < n_points; i++)
		mass_center = mass_center + pointsArray [i];

	mass_center /= double (n_points);

	// Filling info array with angles and distances
	for (size_t i = 0; i < n_points; i++)
		{
		// Point to mass center radius vector
		Vectord deltaMassCenter = mass_center-pointsArray [i];

		// x coord - distance to center
		points [i].x = (deltaMassCenter).length ();
		// y coord - additional angle
		points [i].y = atan2 (deltaMassCenter.dir ().y, deltaMassCenter.dir ().x);
		
		// Calculating radius
		if (points [i].x > radius)
			radius = points [i].x;
		}

	// Calculating total inertia moment of a body
	J = 0;
	for (size_t i = 0; i < n_points; i++)
		J += points [i].x * points [i].x * (mass/n_points) / 3;
	}
Body::~Body ()
	{
 	free (points);
	}

void Body::applyForce (int point, Vectord Force, double dt)
	{

    // Applying force directly to mass center:
    Object::addForce (Force, dt);

	if (0 <= point && point < n_points)
		{
		// That part of the force that is able to rotate the body is equal to
		// the scalar product of the force vector by the unit vector of angle
		// (which is perpendicular to the radius vector from the point 
		// to which the force is applied to the center of mass of the body) 
		//
		// (see picture "body rotation" in folder "explanations")
		double activeForce = Force*Vectord (pi/2 + angle+points [point].y);
		
		// Angular velocity increases proprtional to Torque 
		omega += (activeForce * points [point].x)/J;
		}
	}
void Body::applyAccel (int point, Vectord Accel, double dt)
    { 
    
    if (0 <= point && point < n_points && Object::mass != INFINITY)
        {
        // Applying force directly to mass center:
        Object::addForce (Accel*mass, dt);

        // That part of the force that is able to rotate the body is equal to
        // the scalar product of the force vector by the unit vector of angle
        // (which is perpendicular to the radius vector from the point 
        // to which the force is applied to the center of mass of the body) 
        //
        // (see picture "body rotation" in folder "explanations")
        double activeForce = (Accel*mass)*Vectord (pi/2 + angle+points [point].y);

        // Angular velocity increases proprtional to Torque 
        omega += (activeForce * points [point].x)/J;
        }
    }

void Body::applyForceToVirtual (Vectord virtualPoint, Vectord Force, double dt)
	{ 
	// Applying force directly to mass center:
	Object::addForce (Force, dt);

	// That part of the force that is able to rotate the body is equal to
	// the scalar product of the force vector by the unit vector of angle
	// (which is perpendicular to the radius vector from the point 
	// to which the force is applied to the center of mass of the body) 
	//
	// (see picture "body rotation" in folder "explanations")
	double activeForce = Force*Vectord (pi/2 + angle + 
                                        atan2f (virtualPoint.y - r.y, virtualPoint.x - r.x));

	// Angular velocity increases proprtional to Torque 
	omega += (activeForce * (virtualPoint - r).length ())/J;
	}
void Body::accelerateVirtual (Vectord virtualPoint, Vectord Accel, double dt)
    { 
    if (Object::mass != INFINITY)
        {
        // Applying force directly to mass center:
        Object::addForce (Accel*mass, dt);

        // That part of the force that is able to rotate the body is equal to
        // the scalar product of the force vector by the unit vector of angle
        // (which is perpendicular to the radius vector from the point 
        // to which the force is applied to the center of mass of the body) 
        //
        // (see picture "body rotation" in folder "explanations")
        double activeForce = (Accel*mass)*Vectord (pi/2 + angle + atan2f (virtualPoint.y - r.y, virtualPoint.x - r.x));

        // Angular velocity increases proprtional to Torque 
        omega += (activeForce * (virtualPoint - r).length ())/J;
        }
    }

void Body::update (double dt)
	{
	angle += omega*dt;
	Object::update (dt);
	}

Vectord Body::getPointPos (int point)
	{
	if (0 <= point && point < n_points)
		{
		// Calculating current total angle of point:
		Vectord deltaPos (points [point].y+angle);
		// Multiplying unit direction angle and distance from mass center
		deltaPos = deltaPos*points [point].x;
		// Adding position vector
		deltaPos = deltaPos + r;

		return deltaPos;
		}

	// In case of incorrect point id function returns mass center coordinates
	return r;
	}
double Body::getRadius ()
	{
	return radius;
	}
size_t Body::nPoints ()
	{
	return size_t (n_points);
	}

double Body::getMass ()
    { 
    return mass;
    }

double Body::getKinEnergy ()
    {
    return mass*(v*v)/2.f + J*omega*omega/2.f;
    }

void Body::draw (sf::RenderWindow & window)
	{
	switch (type)
		{
		case objectType::body:
			Draw::body (window, this);
			break;
		case objectType::ground:
			Draw::ground (window, this);
			break;
		default:
			break;
		}
	}
