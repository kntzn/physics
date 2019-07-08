#include "Shapes.h"

Shape::Shape (Vectord * points_array, size_t n_points):
    nPoints (n_points)
    {
    // Memory allocation for points array
    points = (Vectord*) calloc (n_points, sizeof (Vectord));
    if (!points)
        {
        printf ("ERROR: Failed to create points array\n\tfile %s\n\tline %d\n",
                __FILE__,
                __LINE__);
        exit (1);
        }

    // Copying points
    for (size_t i = 0; i < n_points && points_array; i++)
        points [i] = points_array [i];
        
    
    }

Shape::~Shape ()
    {
    }

Vectord Shape::operator[](size_t i) const
    {
    // Security check
    assert (0 <= i);
    assert (i < nPoints);

    return Vectord (points [i]);
    }

Shape::operator size_t() const
    {
    return nPoints;
    }

size_t Shape::get_nPoints ()
    {
    return nPoints;
    }
