#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../cmp/blackBoardComponent.hpp"
#include "../utils/AI.hpp"
#include "../utils/random.hpp"

#include "entityManager.hpp"
#include "SpriteManager.hpp"
#include "mapManager.hpp"



namespace FVeng
{
    struct GameManager
    {
        #define PLAYER_TEXT "player_sprite"
        #define MAP_TEXT    "map_sprite"
        #define HEART_TEXT  "heart_sprite"
<<<<<<< HEAD
        #define COIN_TEXT   "coin_sprite"
        #define CLOCK_TEXT  "clock_sprite"
=======
        #define BULLET_TEXT "bullet_sprite"

>>>>>>> 4ea725d3bb52d340a37e08d66a986de48a621103

        GameManager(sf::RenderWindow& window);

        GameManager (const GameManager&) = delete;
        GameManager (GameManager&&) = delete;
        GameManager& operator=(const GameManager&)= delete;
        GameManager& operator=(GameManager&&)= delete;       
        
        sf::RenderWindow& getWindow();
        void initLevel();
        void initGame();
        game::Entity& createPlayer(FVmath::Point2Di Pos);
        game::Entity& createHeart();
        game::Entity& createCoin();
        game::Entity& createClock();
        void createEnemyArrive(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, double friction,  double perceptionTime);
        void createEnemyPursue(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime);
        void createMap();

        void createBullet(FVmath::Point2Di Pos, FVmath::Point2Di Vel);
        void createSpawner(tXMLeng::Spawner& spawner);
        void createAllSpawner();
        void setRenderNextLayer(game::MapComponent& map);
        void resetMap(game::MapComponent& map);
        void LoadAllTextures();
        void initEntityRender(game::Entity& entity, FVmath::Point2D origin, sf::IntRect TexRect);
        void SpawnDummy(FVmath::Point2Di Pos);

        FVeng::EntityManager<game::Entity>& getEntityManager();
        game::blackBoardComponent& getBB();
        tXMLeng::mapManager& getMapManager();
        game::Entity& getPlayer();


        

        private:

        sf::RenderWindow& window_;
        //create Sprite manager
        SFMLeng::SpriteManager SPman{};
        tXMLeng::mapManager mapMan{};

        FVeng::EntityManager<game::Entity> EM_{100};
        game::blackBoardComponent bb_{} ;
        



    };
}