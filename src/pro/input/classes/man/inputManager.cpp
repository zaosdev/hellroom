#include "inputManager.hpp"

namespace game
{
    InputManager::InputManager(sf::RenderWindow& window)
    : window_(window)
    {
    }

    void InputManager::update()
    {
        sf::Event event;
        while (window_.pollEvent(event)) 
        {
                switch (event.type) 
                {

                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::W: KEY_W = true; break;
                        case sf::Keyboard::A: KEY_A = true; break;
                        case sf::Keyboard::S: KEY_S = true; break;
                        case sf::Keyboard::D: KEY_D = true; break;
                        default: break;
                    }
                break;

                   

                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::W: KEY_W = false; break;
                        case sf::Keyboard::A: KEY_A = false; break;
                        case sf::Keyboard::S: KEY_S = false; break;
                        case sf::Keyboard::D: KEY_D = false; break;
                        default: break;
                    }
                break;

                case sf::Event::Closed: window_.close(); break;

                default:    break;
                }
        }
    }
}
