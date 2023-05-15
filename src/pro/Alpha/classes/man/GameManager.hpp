#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../cmp/blackBoardComponent.hpp"
#include "../utils/AI.hpp"
#include "../utils/random.hpp"
#include "../utils/gameData.hpp"


#include "entityManager.hpp"
#include "SpriteManager.hpp"
#include "mapManager.hpp"
#include "effectManager.hpp"




namespace FVeng
{
    struct GameManager
    {
        #define PLAYER_TEXT "player_sprite"
        #define ENEMY_A     "enemyA_sprite"
        #define ENEMY_B     "enemyB_sprite"   
        #define MAP_TEXT    "map_sprite"
        #define HEART_TEXT  "heart_sprite"
        #define COIN_TEXT   "coin_sprite"
        #define CLOCK_TEXT  "clock_sprite"
        #define BULLET_TEXT "bullet_sprite"
        #define PET1_TEXT   "pet1_sprite"
        #define PET2_TEXT   "pet2_sprite"
        #define PET3_TEXT   "pet3_sprite"
        #define SHIELD_TEXT "shield_sprite"

        GameManager(sf::RenderWindow& window);

        GameManager (const GameManager&) = delete;
        GameManager (GameManager&&) = delete;
        GameManager& operator=(const GameManager&)= delete;
        GameManager& operator=(GameManager&&)= delete;       
        
        sf::RenderWindow& getWindow();
        void initLevel();
        void initGame();
        game::Entity& createPlayer(FVmath::Point2Di Pos);
        game::Entity& createPet   (FVmath::Point2Di Pos);
        game::Entity& createHeart   ();
        game::Entity& createCoin    ();
        game::Entity& createClock   ();
        game::Entity& createShield  ();
        game::Entity& createMapCollider(FVmath::Point2Di Pos);

        void createEnemyArrive(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, double friction,  double perceptionTime);
        void createEnemyPursue(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime);
        void createEnemyShoot (FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime);
        void createMap();
        void changeMap();
        void createHealth(FVmath::Point2D Pos);

        void createBullet(FVmath::Point2Di Pos, FVmath::Point2Di Vel);
        void createEnemyBullet(FVmath::Point2D Pos, FVAI::SB sb, FVmath::Point2D targetCoord);
        void createPetBullet(FVmath::Point2D Pos, FVAI::SB sb, FVmath::Point2D targetCoord);
        void createSpawner(tXMLeng::Spawner& spawner);
        void createAllSpawner();
        void setRenderNextLayer(game::MapComponent& map);
        void resetMap(game::MapComponent& map);
        void LoadAllTextures();
        void initEntityRender(game::Entity& entity, FVmath::Point2D origin, sf::IntRect TexRect);
        void SpawnDummy(FVmath::Point2Di Pos);
        void deleteMap();
        void update();

        FVeng::EntityManager<game::Entity>& getEntityManager();
        game::blackBoardComponent& getBB();
        tXMLeng::mapManager& getMapManager();
        game::Entity& getPlayer();
        
        std::vector<game::Entity::id_type> SpawnersID{}; 
         
        private:

        sf::RenderWindow& window_;
        //create Sprite manager
        SFMLeng::SpriteManager SPman{};
        tXMLeng::mapManager mapMan{};
        FV_factory::effectsFactory effMan{};

        FVeng::EntityManager<game::Entity> EM_{100};
        game::blackBoardComponent bb_{} ;
        bool allSpawned{false};
        game::Entity::id_type mapID_{};
           
    };
}