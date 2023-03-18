#include "inputManager.hpp"


namespace game
{
    InputManager::InputManager(sf::RenderWindow& window) //<<-- fachada de render!!
    : window_(window)
    {
    }

    void InputManager::update()
    {
        Event_t event;
        //std::cout << "Inicio de inputmanager";
        while (window_.pollEvent(event)) 
        {
                switch (event.type) 
                {
                    case KeyPressed:
                        keyStates_[event.key.code] = true;
                        break;

                    case KeyReleased:
                        keyStates_[event.key.code] = false;
                        break;

                    case Closed:
                        window_.close();
                        break;

                    default:
                        break;
                }
        }
    }


    bool InputManager::isKeyPressed(Key key)
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
