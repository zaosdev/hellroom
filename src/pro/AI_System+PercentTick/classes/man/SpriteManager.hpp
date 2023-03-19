#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/math.hpp"

namespace SFMLeng
{

    // struct SFMLSprite
    // {
    //     SFMLSprite()
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
        
        std::size_t  loadTexture(std::string texStr);

        void assignTexture(sf::Sprite& sp, const size_t texIdx);

        void modifyTextureRect(sf::Sprite& sp, sf::IntRect rect);

        void modifySpriteOrigin(sf::Sprite& sp,FVmath::Point2D origin);

        private:

            std::vector<sf::Texture> vecTex_;

    };
}