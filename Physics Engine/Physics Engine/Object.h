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
		Vectorf r, v;
		float mass = 1;
		uint32_t type = unnamed_type;

	public:
		Object (Vectorf Position, float Mass, Vectorf Velocity);
		~Object ();

		void update (float dt);
		void addForce (Vectorf F, float dt);
		void accelerate (Vectorf a, float dt);

		Vectorf getPos ();
		Vectorf getVel ();

		virtual void draw (sf::RenderWindow &window) = 0;

	};

