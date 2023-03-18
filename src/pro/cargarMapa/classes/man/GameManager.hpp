#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
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
        void createPlayer();
        void createMap();
        void LoadAllTextures();
        void initEntityRender(game::Entity& entity, FVmath::vec2D origin, sf::IntRect TexRect);

        FVeng::EntityManager<game::Entity>& getEntityManager();
        

        private:

        sf::RenderWindow window_{};
        tXMLeng::mapManager mapMan{};
        //create Sprite manager
        SFMLeng::SpriteManager SPman{};
        FVeng::EntityManager<game::Entity> EM_{100};


    };
}