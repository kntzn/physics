#include "Object.h"

Object::Object  (Vector <float> Position, float Mass, Vector <float> Velocity)
	{
	r = Position;
	v = Velocity;
	mass = Mass;
	}
Object::~Object ()
	{
	}

void Object::update     (float dt)
	{
	r = r + v*dt;
	}
void Object::addForce   (Vector<float> F, float dt)
	{
	F = F/mass;
	F = F*dt;
	v = v + F;
	}
void Object::accelerate (Vector<float> a, float dt)
	{
	a = a*dt;
	v = v + a;
	}

Vector<float> Object::getPos ()
	{
	return Vector<float> (r);
	}
Vector<float> Object::getVel ()
	{
	return Vector<float> (v);
	}