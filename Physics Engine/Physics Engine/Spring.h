#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class Spring
	{
	private:
		sf::Sprite spring_sprite;
		float scale_const = 1;

		Vectord right, left, Force;
		float hardness = 1;
		float init_dist = 0, curr_dist = 0, delta_dist = 0,
			  max_dist  = 0, min_dist  = 0;
	public:
		Spring (sf::Sprite* spring_spr, Vectord begin, Vectord end, float k);
		~Spring ();

		Vectord getForceRight ();
		Vectord getForceLeft ();

		void update (Vectord begin, Vectord end);
		void draw (sf::RenderWindow &window, bool points = false);

        float getPotEnergy ();
	};
