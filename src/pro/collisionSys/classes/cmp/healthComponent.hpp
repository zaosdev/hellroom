#pragma once 
#include <vector>

namespace game
{
    struct HealthComponent
    {
        float maxLife                         = 1;
        float currentLife                     = 1;
        float positiveAffection               = 0;
        float negativeAffection               = 0;
        double inmortalityTime                = 0; 
        double timePassed                     = 0;
        bool   isInmortal                     = false;
    };
}