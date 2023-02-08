#pragma once
#include <SFML/Graphics.hpp>

namespace FVeng
{
    struct GameManager
    {

        GameManager(int x, int y, std::string nameGame){};
        
        sf::RenderWindow& getWindow() {};


        private:

        sf::RenderWindow window_{};


    };
}