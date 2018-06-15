#include "Object.h"

Object::Object  (Vectord Position, float Mass, Vectord Velocity)
	{
	r = Position;
	v = Velocity;
	mass = Mass;
	}
Object::~Object ()
	{
	}

void Object::update (float dt)
	{
	r += v*dt;
	}
void Object::addForce (Vectord F, float dt)
	{
	v += (F/mass)*dt;
	}
void Object::accelerate (Vectord a, float dt)
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