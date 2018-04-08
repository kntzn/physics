#pragma once
#include "Vector.h"

class Object
	{
	private:
		Vector <float> r, v;
		float mass = 1;

	public:
		Object (Vector <float> Position, float Mass, Vector <float> Velocity);
		~Object ();

		void update (float dt);
		void addForce (Vector <float> F, float dt);
		void accelerate (Vector <float> a, float dt);

		Vector <float> getPos ();
		Vector <float> getVel ();

	};

