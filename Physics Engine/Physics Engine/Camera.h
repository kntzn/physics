#pragma once
#include <SFML/Graphics.hpp>

class Camera: public sf::View
    {
    private:
        float zoomFactor = 1;
    
    public:
        Camera (sf::FloatRect fr)
            {
            reset (fr);
            }

        sf::View scope (float factor)
            {
            sf::View::zoom (1-float (factor));
            zoomFactor /= 1-float (factor);

            return *this;
            }

        float getZoom ()
            {
            return zoomFactor;
            }

    };
