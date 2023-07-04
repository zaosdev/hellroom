#pragma once 

#include "../utils/effectType.hpp"

namespace game
{

    enum class effectState
    {
        inContainer,
        readyToApply,
        applied
    };
    
    struct EffectComponent{

        std::vector<effect_utils::effectType> effects{};
        std::vector<effect_utils::effectType> newEffects{};

        effectState state{effectState::inContainer};
        int affectedPartyID{-1};

    };
}