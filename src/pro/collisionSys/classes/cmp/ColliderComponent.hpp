#pragma once 
// #include <iostream>
#include "../utils/math.hpp"
#include <SFML/Graphics.hpp>
// #include "SpriteManager.hpp"

namespace game {

    struct ColliderComponent{

        // sf::Sprite Sprite;
        // sf::FloatRect floatBounds;
        // sf::IntRect intBounds;

        // ColliderComponent() {
        //     floatBounds = Sprite.getGlobalBounds();
        //     intBounds = sf::IntRect(
        //         static_cast<int>(floatBounds.left),
        //         static_cast<int>(floatBounds.top),
        //         static_cast<int>(floatBounds.width),
        //         static_cast<int>(floatBounds.height)
        //     );
        // }

        sf::FloatRect BBox{};

        //FVmath::Rect2D BBox{};
    };
    
}
