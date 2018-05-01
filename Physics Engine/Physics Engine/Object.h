#pragma once
#include "Vector.h"

enum objectType
	{
	unnamed_type,
	body,
	ground
	};

class Object
	{
	protected:
		Vector <float> r, v;
		float mass = 1;
		uint32_t type = unnamed_type;

	public:
		Object (Vector <float> Position, float Mass, Vector <float> Velocity);
		~Object ();

		void update (float dt);
		void addForce (Vector <float> F, float dt);
		void accelerate (Vector <float> a, float dt);

		Vector <float> getPos ();
		Vector <float> getVel ();

	};

