#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class Spring
	{
	private:
		sf::Sprite spring_sprite;
		float scale_const = 1;

		Vector <float> right, left, Force;
		float hardness = 1;
		float init_dist = 0, curr_dist = 0, delta_dist = 0,
			  max_dist  = 0, min_dist  = 0;
	public:
		Spring (sf::Sprite* spring_spr, Vector <float> begin, Vector <float> end, float k);
		~Spring ();

		Vector <float> getForceRight ();
		Vector <float> getForceLeft ();

		void update (Vector <float> begin, Vector <float> end);
		void draw (sf::RenderWindow &window, bool points = false);
	};

