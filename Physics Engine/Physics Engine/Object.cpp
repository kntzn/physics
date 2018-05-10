#include "Object.h"

Object::Object  (Vectorf Position, float Mass, Vectorf Velocity)
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
void Object::addForce (Vectorf F, float dt)
	{
	v += (F/mass)*dt;
	}
void Object::accelerate (Vectorf a, float dt)
	{
	v += a*dt;
	}

Vectorf Object::getPos ()
	{
	return r;
	}
Vectorf Object::getVel ()
	{
	return v;
	}