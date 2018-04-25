#pragma once
#include <math.h>
#include <SFML/System.hpp>

template <typename dataType> class Vector
	{
	public:
		dataType x = 0, y = 0;

		Vector ()
			{
			}
		Vector (dataType X, dataType Y)
			{
			x = X;
			y = Y;
			}
		Vector (dataType alpha)
			{
			x = cos (alpha);
			y = sin (alpha);
			}

		Vector operator+ (Vector const lvec)
			{
			return Vector (lvec.x + x, lvec.y + y);
			};
		Vector operator- (Vector const lvec)
			{
			return Vector (x - lvec.x, y - lvec.y);
			};
		dataType operator* (Vector const lvec)
			{
			return lvec.x*x + lvec.y*y;
			};
		Vector operator* (float factor)
			{
			return Vector (x*factor, y*factor);
			};
		Vector operator- ()
			{
			return Vector (-x, -y);
			};
		Vector operator/ (const float factor)
			{
			return Vector (x/factor, y/factor);
			};

		dataType size ()
			{
			return sqrt (x*x + y*y);
			}
		Vector dir ()
			{
			return Vector (x/size(), y/size());
			}
		sf::Vector2f toSf ()
			{
			return sf::Vector2f (x, y);
			}

	};