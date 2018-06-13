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
		float mass = 1;
		size_t type = unnamed_type;

	public:
		Object (Vectord Position, float Mass, Vectord Velocity);
		~Object ();

		void update (float dt);
		void addForce (Vectord F, float dt);
		
		void accelerate (Vectord a, float dt);

		Vectord getPos ();
		Vectord getVel ();
		size_t getType ();
	
	};

