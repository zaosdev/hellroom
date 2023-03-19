#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../facade/inputFacade.hpp"

namespace game
{

    struct InputManager
    {
        InputManager(sf::RenderWindow& window); // <<-- fachada de render!!


        InputManager (const InputManager&) = delete;
        InputManager (InputManager&&) = delete;
        InputManager& operator=(const InputManager&)= delete;
        InputManager& operator=(InputManager&&)= delete;

        void update();

        bool isKeyPressed(Key key);
        
        // bool isWPressed() { return KEY_W; }
        // bool isAPressed() { return KEY_A; }
        // bool isSPressed() { return KEY_S; }
        // bool isDPressed() { return KEY_D; }

        private:
            sf::RenderWindow& window_;
            std::unordered_map<Key, bool> keyStates_;
    };

}

    
