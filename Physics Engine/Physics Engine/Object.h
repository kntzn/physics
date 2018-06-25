#pragma once
#include "Vector.h"
#include <SFML\Graphics.hpp>

enum objectType
	{
	unnamed_type,
	body,
	ground
	};

class Object
	{
	protected:
		Vectord r, v;
		double mass = 1;
		size_t type = unnamed_type;

	public:
		Object (Vectord Position, double Mass, Vectord Velocity);
		~Object ();

		void update (double dt);
		void addForce (Vectord F, double dt);
		void accelerate (Vectord a, double dt);

		Vectord getPos ();
		Vectord getVel ();
		size_t getType ();
	
	};

