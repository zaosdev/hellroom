#include "SpriteManager.hpp"
#include <iostream>

namespace SFMLeng
{

    SpriteManager::SpriteManager() = default;


    void SpriteManager::assignTexture(sf::Sprite& sp, const size_t texIdx)
    {
        auto& tex = vecTex_[texIdx];
        sp.setTexture(tex);
    }

    void SpriteManager::modifyTextureRect(sf::Sprite& sp, sf::IntRect rect)
    {
        sp.setTextureRect(rect);
    }

    void SpriteManager::modifySpriteOrigin(sf::Sprite& sp,FVmath::Point2D origin)
    {
        sp.setOrigin(origin.x,origin.y);
    }

    std::size_t SpriteManager::loadTexture( std::string texStr)
    {
        auto& tex = vecTex_.emplace_back();
        if (!tex.loadFromFile(texStr)) {
            std::cerr << "Error cargando la imagen sprites.png";
            exit(0);
        }
        else
        {
            return vecTex_.size()-1;
        }

    }
}