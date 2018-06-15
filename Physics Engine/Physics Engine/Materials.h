#pragma once

namespace MATERIAL
    {
    struct Material
        {
        float elasticity;

        Material (float ELAST)
            { 
            elasticity = ELAST;
            }
        };

    Material RussianGround  (9999 + 1);
    Material PindosiaGround (69);

    Material SpringSteel (100);
    };