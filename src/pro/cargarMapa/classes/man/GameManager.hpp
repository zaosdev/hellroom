#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "mapManager.hpp"



namespace FVeng
{
    struct GameManager
    {

        GameManager(int x, int y, std::string nameGame);

        GameManager (const GameManager&) = delete;
        GameManager (GameManager&&) = delete;
        GameManager& operator=(const GameManager&)= delete;
        GameManager& operator=(GameManager&&)= delete;       
        
        sf::RenderWindow& getWindow();
        void initLevel();


        game::Entity* ent;
        private:

        sf::RenderWindow window_{};
        tXMLeng::mapManager mapMan{};



    };
}