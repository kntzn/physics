#pragma once
#include "Vector.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// ------------------------------------------------------------
// Shape class is a simple container for points arrays and is
// being used as the more flexible way to store
// the bodys' shapes
// ------------------------------------------------------------
class Shape
    {
    private:
        size_t nPoints;
        Vectord * points;

    public:
        // Constructs the shape from the array of vectors.
        // Points are being copied, pointer to points is not being saved
        Shape (Vectord * points, size_t nPoints);
        ~Shape ();

        // Returns the i-th point of the shape
        Vectord operator[] (size_t i) const;
        // Casting to size_t returns nPoints
        operator size_t () const;
        // Classic getter that does just the same
        size_t get_nPoints ();
    };
