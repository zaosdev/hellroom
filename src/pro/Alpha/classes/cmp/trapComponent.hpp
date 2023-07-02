#pragma once 
#include <array>

namespace game
{
    enum estado
    {
        primero,segundo,tercero,cuarto
    };
    struct TrapComponent
    {
        estado modo{estado::primero};
        float delayTime {5};
        float trapDamage {100};
    };
}