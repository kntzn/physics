#pragma once
#include "Vector.h"

class Object
	{
	protected:
		Vector <float> r, v;
		float mass = 1;

	public:
		Object (Vector <float> Position, float Mass, Vector <float> Velocity)
			{ 
			r = Position;
			v = Velocity;
			mass = Mass;
			}
		~Object ()
			{ 
			}

		void update (float dt)
			{ 
			r = r + v*dt;
			}
		void addForce (Vector <float> F, float dt)
			{
			F = F/mass;
			F = F*dt;
			v = v + F;
			}
		void accelerate (Vector <float> a, float dt);

		Vector <float> getPos ()
			{
			return Vector<float> (r);
			}
		Vector <float> getVel ()
			{ 
			return Vector<float> (v);
			}

	};

