#pragma once 
#include <SFML/Graphics.hpp>

namespace game
{
    struct RenderComponent
    {
        sf::Texture tex{};
        sf::Sprite Sprite{};
    };
}