#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"



namespace game
{
    struct CollisionSys
    {
        CollisionSys(FVeng::GameManager& gameMan/*, SFMLeng::SpriteManager& spriteMan*/);
        ~CollisionSys();

        CollisionSys (const CollisionSys&) = delete;
        CollisionSys (CollisionSys&&) = delete;
        CollisionSys& operator=(const CollisionSys&)= delete;
        CollisionSys& operator=(CollisionSys&&)= delete;

        //bool checkCollision(const sf::FloatRect bbox1, const sf::FloatRect bbox2); //comprueba si hay colisión entre dos sprites usando su bounding box
        //void collisionDetect(const std::vector<sf::FloatRect>& bboxes); //comprueba colisiones y realiza las acciones necesarias
        //void colliding();
        void noOverlap(game::Entity& ent1, game::Entity& ent2);
        void update(); //gestionara las colisiones
        

        Entity* prevEnt;
    
        sf::FloatRect player_bbox;
        sf::FloatRect enemy_bbox;


        private:
            FVeng::GameManager& gMan_;
           // SFMLeng::SpriteManager& spriteMan_; 
            
    };
}