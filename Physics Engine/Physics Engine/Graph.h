#pragma once
#include <deque>
#include <SFML/Graphics.hpp>
#include "Camera.h"

class Graph: private std::deque <double>
    {
    private:
        
        int arrayLength = 0;
        double dataMin = INFINITY;
        double dataMax = -INFINITY;
        double dataStart = 0;

        sf::Color graphColor;

    public:
        Graph (unsigned int length, sf::Color color);
        ~Graph ();

        void addPoint (double point)
            { 
            if (point > dataMax)
                dataMax = point;
            if (point < dataMin)
                dataMin = point;
            if (empty ())
                dataStart = point;

            push_back (point);

            if (size () > arrayLength)
                pop_front ();    
            }

        void draw (sf::RenderWindow &window, Camera camera)
            { 
            float additionalYoffset = window.getSize ().y/2;

            float divider = ((fabs (dataMax) > fabs (dataMin)) ? fabs (dataMax) : fabs (dataMin));

            int i = 0;
            for (auto iter = ++begin (); iter != end (); iter++)
                {                
                sf::Vertex line [] =
                    {
                    sf::Vertex (sf::Vector2f (i, additionalYoffset - (*iter     - dataStart)/divider*additionalYoffset), graphColor),
                    sf::Vertex (sf::Vector2f (i, additionalYoffset - (*(iter-1) - dataStart)/divider*additionalYoffset), graphColor)
                    };

                window.draw (line, 2, sf::PrimitiveType::Lines);

                i++;
                }
            }

        
    };

