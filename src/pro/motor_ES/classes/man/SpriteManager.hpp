#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/math.hpp"

namespace SFMLeng
{
    struct SpriteManager
    {

        SpriteManager();
        
        void loadTexture(sf::Texture& tex, std::string texStr);

        void assignTexture(sf::Sprite& sp, sf::Texture& Tex);

        void SpriteManager::modifyTextureRect(sf::Sprite& sp, sf::IntRect rect);

        void SpriteManager::modifySpriteOrigin(sf::Sprite& sp,FVmath::vec2D origin);

        private:

    };
}