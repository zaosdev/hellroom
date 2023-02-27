#pragma once
#include "../man/GameManager.hpp"
#include <iostream>

namespace game
{

    struct InputSys
    {
        InputSys(FVeng::GameManager& gameMan);


        InputSys (const InputSys&) = delete;
        InputSys (InputSys&&) = delete;
        InputSys& operator=(const InputSys&)= delete;
        InputSys& operator=(InputSys&&)= delete;

        void update();

        private:
            FVeng::GameManager& gMan_;
            std::vector<sf::Event> events_;
    };

}