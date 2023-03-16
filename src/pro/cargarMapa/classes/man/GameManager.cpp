#include "GameManager.hpp"

namespace FVeng
{
        GameManager::GameManager(int x, int y, std::string nameGame)
        : window_(sf::VideoMode(x, y), nameGame)
        {
            ent = new game::Entity;
            window_.setKeyRepeatEnabled(true); // Habilitar entrada de teclado repetido
            window_.setFramerateLimit(60);
        }

        sf::RenderWindow& GameManager::getWindow()
        {
            return window_;
        }

        void GameManager::initLevel()
        {
            mapMan.loadMap("media/Mapa1.tmx");
        }

}