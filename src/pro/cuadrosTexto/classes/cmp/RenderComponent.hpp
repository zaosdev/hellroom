#pragma once 
#include <SFML/Graphics.hpp>
#include "../utils/math.hpp"


namespace game
{
    struct RenderComponent
    {
        sf::Texture tex{};
        sf::Sprite Sprite{};
        FVmath::vec2Di window_Pos{};
    };
}