#pragma once
#include "../man/GameManager.hpp"
#include "../man/inputManager.hpp"
#include "../sys/soundSys.hpp"
#include "../sys/dialogueSys.hpp"
#include <iostream>

namespace game
{

    struct InputSys
    {
        InputSys(FVeng::GameManager& gameMan, InputManager& intpRec, SoundSys& soundSys, DialogueSys& dialSys);

        InputSys (const InputSys&) = delete;
        InputSys (InputSys&&) = delete;
        InputSys& operator=(const InputSys&)= delete;
        InputSys& operator=(InputSys&&)= delete;

        void update();

        private:
            FVeng::GameManager& gMan_;
            InputManager&       inpRec_;
            SoundSys&           soundSys;
            DialogueSys&        dialogueSys;
    };

}