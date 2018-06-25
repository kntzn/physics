#pragma once

namespace MATERIAL
    {
    struct Material
        {
        double elasticity;

        Material (double ELAST)
            { 
            elasticity = ELAST;
            }
        };

    Material RussianGround  (9999 + 1);
    Material PindosiaGround (69);

    Material SpringSteel (100);
    };