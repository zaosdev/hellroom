#pragma once

#include "../man/GameManager.hpp"
#include "../man/SpriteManager.hpp"



namespace game
{
    struct CollisionSys
    {
        CollisionSys(FVeng::GameManager& gameMan, SFMLeng::SpriteManager& spriteMan);
        ~CollisionSys();

        CollisionSys (const CollisionSys&) = delete;
        CollisionSys (CollisionSys&&) = delete;
        CollisionSys& operator=(const CollisionSys&)= delete;
        CollisionSys& operator=(CollisionSys&&)= delete;

        //bool checkCollision(const sf::FloatRect bbox1, const sf::FloatRect bbox2); //comprueba si hay colisión entre dos sprites usando su bounding box
        //void collisionDetect(const std::vector<sf::FloatRect>& bboxes); //comprueba colisiones y realiza las acciones necesarias
        void colliding(bool collision);
        void update(); //gestionara las colisiones


        private:
            FVeng::GameManager& gMan_;
            SFMLeng::SpriteManager& spriteMan_;
    };
}