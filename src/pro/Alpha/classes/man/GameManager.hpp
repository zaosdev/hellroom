#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../cmp/blackBoardComponent.hpp"
#include "../utils/AI.hpp"
#include "entityManager.hpp"
#include "SpriteManager.hpp"
#include "mapManager.hpp"



namespace FVeng
{
    struct GameManager
    {
        #define PLAYER_TEXT "player_sprite"
        #define MAP_TEXT "map_sprite"


        GameManager(int x, int y, std::string nameGame);

        GameManager (const GameManager&) = delete;
        GameManager (GameManager&&) = delete;
        GameManager& operator=(const GameManager&)= delete;
        GameManager& operator=(GameManager&&)= delete;       
        
        sf::RenderWindow& getWindow();
        void initLevel();
        void initGame();
        game::Entity& createPlayer();
        void createEnemyArrive(FVmath::Point2D Pos,FVmath::Point2D targetCoord, double friction,  double perceptionTime);
        void createEnemyPursue(FVmath::Point2D Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime);
        void createMap();
        void LoadAllTextures();
        void initEntityRender(game::Entity& entity, FVmath::Point2D origin, sf::IntRect TexRect);

        FVeng::EntityManager<game::Entity>& getEntityManager();
        game::blackBoardComponent& getBB();
        

        private:

        sf::RenderWindow window_{};
        tXMLeng::mapManager mapMan{};
        //create Sprite manager
        SFMLeng::SpriteManager SPman{};
        FVeng::EntityManager<game::Entity> EM_{100};
        game::blackBoardComponent bb_{} ;
        



    };
}