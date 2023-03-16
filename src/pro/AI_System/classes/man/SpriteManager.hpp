#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/math.hpp"

namespace SFMLeng
{

    // struct SFMLSprite
    // {
    //     SFMLSprite(std::string tex)
    //     {

    //     }

    //     sf::Sprite sp;
    //     sf::Texture tex;
    //     //std::array<sf::IntRect> rect;
    // };

    struct SpriteManager
    {

        SpriteManager();

        SpriteManager (const SpriteManager&) = delete;
        SpriteManager (SpriteManager&&) = delete;
        SpriteManager& operator=(const SpriteManager&)= delete;
        SpriteManager& operator=(SpriteManager&&)= delete;
        
        void loadTexture(sf::Texture& tex, std::string texStr);

        void assignTexture(sf::Sprite& sp, sf::Texture& Tex);

        void modifyTextureRect(sf::Sprite& sp, sf::IntRect rect);

        void modifySpriteOrigin(sf::Sprite& sp,FVmath::vec2D origin);

        private:

    };
}