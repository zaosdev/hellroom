#include "SpriteManager.hpp"
#include <iostream>

namespace SFMLeng
{



    void SpriteManager::assignTexture(sf::Sprite& sp, sf::Texture&  Tex)
    {
        sp.setTexture(Tex);
    }

    void SpriteManager::modifyTextureRect(sf::Sprite& sp, sf::IntRect rect)
    {
        sp.setTextureRect(rect);
    }

    void SpriteManager::modifySpriteOrigin(sf::Sprite& sp,FVmath::vec2D origin)
    {
        sp.setOrigin(origin.x,origin.y);
    }


    void SpriteManager::loadTexture(sf::Texture& tex, std::string texStr)
    {
        if (!tex.loadFromFile("resources/sprites.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    }
}