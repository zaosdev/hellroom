#include "GameManager.hpp"

namespace FVeng
{
        GameManager::GameManager(int x, int y, std::string nameGame)
        : window_(sf::VideoMode(x, y), nameGame)
        {
            window_.setFramerateLimit(60); //Limit FPS
        } 

        sf::RenderWindow& GameManager::getWindow()
        {
            return window_;
        }

        FVeng::EntityManager<game::Entity>& GameManager::getEntityManager()
        {
            return EM_;
        }


        // auto GameManager::first_valid() {
        //     auto valid = [](Entity const& e) {
        //         return e.alive() && e.collider && e.physics;
        //     };
        //     for(auto& e : EntityManager)
        // }

}