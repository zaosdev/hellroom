#include "animationSys.hpp"

namespace game{
    animationSys::animationSys(sf::Texture* texture,sf::Vector2u imageCount, float switchTime){

        this->imageCount = imageCount;
        this->switchTime = switchTime;

        totalTime = 0.0f;

        currentImage.x = 0;

        uvRect.width = texture->getSize().x / float(imageCount.x);
        uvRect.height = texture->getSize().y / float(imageCount.y);

    }


    void animationSys::update(int row, float deltaTime){

            currentImage.y = row;
            totalTime += deltaTime;

            if(totalTime >= switchTime){
                totalTime = deltaTime; 
                currentImage.x++;

                if(currentImage.x > imageCount.x){
                    currentImage.x = 0;
                }
            }

            uvRect.left = currentImage.x * uvRect.width;
            uvRect.top = currentImage.y * uvRect.height;
    }
}