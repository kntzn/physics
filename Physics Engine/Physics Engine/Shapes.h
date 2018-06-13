#pragma once
#include "Vector.h"
#include "Constants.h"

namespace Obj_Shape
	{
    Vectord* truePolygon (size_t n_points, float radius, float add_angle = 0)
		{
        Vectord* points_address = (Vectord*) calloc (n_points, sizeof (Vectord));
		if (points_address == nullptr)
			printf ("Failed to create points array\n");
		else
			{
			for (int i = 0; i < n_points; i++)
				points_address [i] = Vectord ((float (i)/n_points)*(2.f*pi) + add_angle)*radius;
			}

		return points_address;
		}

	Vectord* rectangle (Vectord size)
		{ 
		Vectord* points_address = (Vectord*) calloc (4, sizeof (Vectord));
		if (points_address == nullptr)
			printf ("Failed to create points array\n");
		else
			{
			points_address [0].x = points_address [3].x = -size.x/2.f;
			points_address [0].y = points_address [1].y = -size.y/2.f;
			points_address [1].x = points_address [2].x =  size.x/2.f;
			points_address [2].y = points_address [3].y =  size.y/2.f;
			}

		return points_address;
		}
	};
