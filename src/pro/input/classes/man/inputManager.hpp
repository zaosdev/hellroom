#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace game
{

    struct InputManager
    {
        InputManager(sf::RenderWindow& window);


        InputManager (const InputManager&) = delete;
        InputManager (InputManager&&) = delete;
        InputManager& operator=(const InputManager&)= delete;
        InputManager& operator=(InputManager&&)= delete;

        void update();

        
        bool isWPressed() { return KEY_W; }
        bool isAPressed() { return KEY_A; }
        bool isSPressed() { return KEY_S; }
        bool isDPressed() { return KEY_D; }

        private:
            sf::RenderWindow& window_;
            bool KEY_W {false};
            bool KEY_A {false};
            bool KEY_S {false};
            bool KEY_D {false};
    };

}

    
