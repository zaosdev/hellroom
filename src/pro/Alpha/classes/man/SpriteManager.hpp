#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/math.hpp"
#include <unordered_map>

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
        
        std::size_t  loadTexture(std::string texStr, const char* textName);

        void assignTexture(sf::Sprite& sp, int);

        void modifyTextureRect(sf::Sprite& sp, sf::IntRect rect);

        void modifySpriteOrigin(sf::Sprite& sp,FVmath::Point2D origin);

        sf::Texture& getTextureByName(const char*);

        int getTextureIdxByName(const char*);


        private:

         std::vector<sf::Texture> vecTex_;
         std::unordered_map<const char*, int> TextureIndexList_;

    };
}