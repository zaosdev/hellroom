#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"
#include "../utils/math.hpp"
#include "../sys/soundSys.hpp"




namespace game
{
    struct expandedTarget
    {
        FVmath::Point2D pos{};
        FVmath::Point2D size{};
    };

    struct CollisionSys
    {
        CollisionSys(FVeng::GameManager& gameMan, game::SoundSys& soundSys /*, SFMLeng::SpriteManager& spriteMan*/);
        ~CollisionSys();

        CollisionSys (const CollisionSys&) = delete;
        CollisionSys (CollisionSys&&) = delete;
        CollisionSys& operator=(const CollisionSys&)= delete;
        CollisionSys& operator=(CollisionSys&&)= delete;

        bool checkCollision(Entity& collider1, Entity& collider2); //comprueba si hay colisión entre entidades
        bool rayVsEntity(const FVmath::Point2D rayOrigin, const FVmath::Point2D rayDirection, expandedTarget& target,Entity& dynamicEntity);

        bool DynamicEntityVsStaticEntity(Entity& dynamicEntity, const float dt, Entity& staticEntity);

        bool ResolveDynamicEntityVsEntity(Entity& dynamicEntity, Entity& staticEntity, const float dt);
        //void resolveCollision(Entity& movingEntity, Entity& staticEntity); //Only works for 1 moving entity against a static one
        //void collisionDetect(const std::vector<sf::FloatRect>& bboxes); //comprueba colisiones y realiza las acciones necesarias
        //void colliding();
        
        //void actOnCollision(auto action);
        void noOverlap(Entity& sprite1, Entity& sprite2);
        void playerCollision(float intersectX, float intersectY,  float deltaX,  float deltaY, Entity& ent2, FVmath::Point2D ent2POS );
        //void shieldCollision(float intersectX, float intersectY,  float deltaX,  float deltaY, Entity& ent1, FVmath::Point2D ent1POS, Entity& ent2, FVmath::Point2D ent2POS );

        //void noOverlap(sf::Sprite& sprite1, sf::Sprite& sprite2);
        void update(float dt); //gestionara las colisiones
        
       // float push = 1.0f;

        Entity* prevEnt;
    
        sf::FloatRect playerBbox;
        sf::FloatRect enemyBbox;
    

        private:
            FVeng::GameManager& gMan_;
            game::SoundSys&     soundSys_;
            //tXMLeng::mapManager::TileMap map_{};
           // SFMLeng::SpriteManager& spriteMan_; 
            
    };
}