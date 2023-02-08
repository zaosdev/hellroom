#include "GameManager.hpp"

namespace FVeng
{
        GameManager::GameManager(int x, int y, std::string nameGame)
        : window_(sf::VideoMode(x, y), nameGame)
        {
        }

        sf::RenderWindow& GameManager::getWindow()
        {
            return window_;
        }
}