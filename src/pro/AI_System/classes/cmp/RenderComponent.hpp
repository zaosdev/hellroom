#pragma once 
#include <SFML/Graphics.hpp>
#include "../utils/math.hpp"


namespace game
{
    struct RenderComponent
    {
        std::size_t         texIndex{};
        sf::Sprite          Sprite{};
        FVmath::Point2Di    window_Pos{};
    };
}