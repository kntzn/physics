#pragma once
#include "Vector.h"
#include "Constants.h"

Vectorf* truePolygon (size_t n_points, float radius, float add_angle = 0)
	{ 
	Vectorf* points_address = (Vectorf*) calloc (n_points, sizeof (Vectorf));
	if (points_address == nullptr)
		printf ("Failed to create points array\n");
	else
		{
		for (int i = 0; i < n_points; i++)
			points_address [i] = Vectorf ((float (i)/n_points)*(2.f*pi) + add_angle)*radius;
		}

	return points_address;
	}