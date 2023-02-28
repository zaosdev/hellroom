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
                        keyStates_[event.key.code] = true;
                        break;

                    case sf::Event::KeyReleased:
                        keyStates_[event.key.code] = false;
                        break;

                    case sf::Event::Closed:
                        window_.close();
                        break;

                    default:
                        break;
                }
        }
    }


    bool InputManager::isKeyPressed(sf::Keyboard::Key key)
    {
        auto it = keyStates_.find(key);
        if (it != keyStates_.end()) //if found, can be true or false
        {
            return it->second;
        } 
        else //if not found, never pressed
        {
            return false;
        }
    }
}
