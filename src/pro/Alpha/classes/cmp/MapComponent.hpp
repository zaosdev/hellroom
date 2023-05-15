#pragma once 

#include "../utils/FVSprite.hpp"




namespace game
{
    struct MapComponent 
    {
        int texIndex{};
        sfml_util::FVSprite FVSprite{};
        int maxLowerLayer{0};
        bool mapCollider{false};
        
    };
}