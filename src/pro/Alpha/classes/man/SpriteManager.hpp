#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/math.hpp"
#include <unordered_map>
#include <vector>

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
        using Texture_type = sf::Texture;
        using Sprite_type = sf::Sprite;
        using rect_f_type = sf::FloatRect;
        using rect_i_type = sf::IntRect;


        SpriteManager();

        SpriteManager (const SpriteManager&) = delete;
        SpriteManager (SpriteManager&&) = delete;
        SpriteManager& operator=(const SpriteManager&)= delete;
        SpriteManager& operator=(SpriteManager&&)= delete;
        
        std::size_t  loadTexture(std::string texStr, const char* textName);

        void assignTexture(Sprite_type& sp, int);

        void modifyTextureRect(Sprite_type& sp,rect_i_type rect);

        void modifySpriteOrigin(Sprite_type& sp,FVmath::Point2D origin);

        Texture_type& getTextureByName(const char*);

        int getTextureIdxByName(const char*);

        // rect_f_type bbox;
        // std::vector<rect_f_type> bboxes;

        private:

         std::vector<Texture_type> vecTex_;
         std::unordered_map<const char*, int> TextureIndexList_;

    };
}