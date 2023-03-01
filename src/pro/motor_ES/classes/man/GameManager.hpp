#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/entityManager.hpp"



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

        FVeng::EntityManager<game::Entity> & getEntityManager();


        game::Entity* ent;
        private:

        FVeng::EntityManager<game::Entity> EM_;
        sf::RenderWindow window_{};



    };
}