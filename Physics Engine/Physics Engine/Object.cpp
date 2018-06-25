#include "Object.h"

Object::Object  (Vectord Position, double Mass, Vectord Velocity)
	{
	r = Position;
	v = Velocity;
	mass = Mass;
	}
Object::~Object ()
	{
	}

void Object::update (double dt)
	{
	r += v*dt;
	}
void Object::addForce (Vectord F, double dt)
	{
	v += (F/mass)*dt;
	}
void Object::accelerate (Vectord a, double dt)
	{
    if (mass == INFINITY)
        a = Vectord (0, 0);
    
    v += a*dt;
	}

Vectord Object::getPos ()
	{
	return r;
	}
Vectord Object::getVel ()
	{
	return v;
	}
size_t Object::getType ()
	{
	return type;
	}