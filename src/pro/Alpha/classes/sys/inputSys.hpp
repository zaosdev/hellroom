#pragma once
#include "../man/GameManager.hpp"
#include "../man/inputManager.hpp"
#include "../sys/soundSys.hpp"
#include "../sys/dialogueSys.hpp"
#include "../man/stateManager.hpp"
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
        bool IsGamePaused();
        void unPause();

        private:
            FVeng::GameManager&        gMan_;
            InputManager&              inpRec_;
            SoundSys&                  soundSys;
            DialogueSys&               dialogueSys;
            bool                       gameIsPaused_ {false};
            int                        cycles_ {0};
            const int                  min_cycles {30};
    };

}