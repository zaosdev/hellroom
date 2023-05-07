#include "SpriteManager.hpp"
#include <iostream>

namespace SFMLeng
{

    SpriteManager::SpriteManager() = default;


    void SpriteManager::assignTexture(sf::Sprite& sp, int idx)
    {
        auto& tex =  vecTex_[idx];
        sp.setTexture(tex);
        // bbox = sp.getGlobalBounds();
        // bboxes.push_back(bbox);
    }

    void SpriteManager::modifyTextureRect(sf::Sprite& sp, sf::IntRect rect)
    {
        sp.setTextureRect(rect);
    }

    void SpriteManager::modifySpriteOrigin(sf::Sprite& sp,FVmath::Point2D origin)
    {
        sp.setOrigin(origin.x,origin.y);
    }

    std::size_t SpriteManager::loadTexture( std::string texStr, const char* textName)
    {
        auto& tex = vecTex_.emplace_back();
        if (!tex.loadFromFile(texStr)) {
            std::cerr << "Error cargando la imagen sprites.png";
            exit(0);
        }
        else
        {
            TextureIndexList_[textName] = vecTex_.size()-1;
            return vecTex_.size()-1;
        }

    }

    sf::Texture& SpriteManager::getTextureByName(const char* textureName)
    {
        auto idx = TextureIndexList_[textureName];
        auto& tex =  vecTex_[idx];
        return tex;
    }

    int SpriteManager::getTextureIdxByName(const char* textureName)
    {
        return TextureIndexList_[textureName];
    }


}