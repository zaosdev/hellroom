#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../man/GameManager.hpp"

namespace game {

    struct animationSys{

        //public:

        animationSys(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

        // animationSys (const animationSys&) = delete;
        // animationSys (animationSys&&) = delete;
        // animationSys& operator=(const animationSys&)= delete;
        // animationSys& operator=(animationSys&&)= delete;


        void update(int row, float deltaTime);

        sf::IntRect uvRect;

        private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;

       

    };
}

