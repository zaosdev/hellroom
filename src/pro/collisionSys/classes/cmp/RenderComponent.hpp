#pragma once 

#include "../utils/FVSprite.hpp"
#include "../utils/math.hpp"



namespace game
{
    struct RenderComponent 
    {
        int texIndex{};
        sf::Sprite Sprite{};
        FVmath::Point2Di window_Pos{};
        
    };
}