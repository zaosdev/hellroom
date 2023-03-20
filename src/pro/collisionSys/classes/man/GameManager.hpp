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

        auto first(auto Valid){
            for(auto& e : EM_){
                if(Valid(e))
                    return EntityManager::entity_iterator(&e);
            }
            return EM_.end();
        }

        auto next(EntityManager::entity_iterator const it, auto Valid){
            if(it < EM_.end())
                return std::find_if(it + 1, EM_.end(), Valid);
            return EM_.end();
        }

        private:

        FVeng::EntityManager<game::Entity> EM_{100};
        sf::RenderWindow window_{};


    };
}