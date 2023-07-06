#pragma once 

namespace game
{
    struct DataComponent
    {
        int coins = 0;
        int pet1  = 0;     // 0 = no comprado
        int pet2  = 0;
        int pet3  = 0;
        int activePet = 0; // 0 = ninguna
        int max_level = 0;
    };
}