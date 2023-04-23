#pragma once
#include "../man/GameManager.hpp"
#include "../man/inputManager.hpp"
#include <iostream>

namespace game
{

    struct InputSys
    {
        InputSys(FVeng::GameManager& gameMan, InputManager& intpRec);

        InputSys (const InputSys&) = delete;
        InputSys (InputSys&&) = delete;
        InputSys& operator=(const InputSys&)= delete;
        InputSys& operator=(InputSys&&)= delete;

        void update();

        private:
            FVeng::GameManager& gMan_;
            InputManager&       inpRec_;
    };

}