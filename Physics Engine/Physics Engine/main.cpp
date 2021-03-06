/*
  Physics Engine 2.1
  main.cpp

  Created by kntzn on 05.07.2019 20:48 GMT+3.
  Copyright � 2019 kntzn. All rights reserved.

  This file is just a sandbox.
  Engine itself is a library.
  Most of the methods, classes etc came from PE2.
  Version 2.1 is improved version of the PE2

*/

#include "PE21.h"

/*
Quick description:

General Objects:

Bodies:
MPoint (Object)
Mpoint -> Body 
          Body -> Ground
          Body -> Tire
       
Interactions:
Pair| + Spring    -> SpringPair
    | + Gravity   -> GravityPair
    | + Collision -> CollisionPair
    | + Rigid     -> RigidPair
    |

*/

#include <iostream>
//#include <SFML\Graphics.hpp>

int main ()
    { 
    PE21 physeng;

    Shape s (nullptr, 20);

    std::cout << size_t (s) << std::endl;

    Body b (Vectord (0, 0), 1.0, Vectord (1, 0), 0, nullptr);

    const double dt_c = 0.016f;

    for (int i = 0; i < 1000; i++)
        { 
        }

    system ("pause");
    }