#pragma once

#include "../man/GameManager.hpp"
#include "../sys/renderSys.hpp"
#include "../sys/soundSys.hpp"

namespace game
{
    struct CofreSys
    {
        CofreSys(FVeng::GameManager& gameMan, game::SoundSys& soundSys);
        ~CofreSys();

        CofreSys (const CofreSys&) = delete;
        CofreSys (CofreSys&&) = delete;
        CofreSys& operator=(const CofreSys&)= delete;
        CofreSys& operator=(CofreSys&&)= delete;

        //void iniPhysicsSys();
        void update();
     


        private:
            FVeng::GameManager& gMan_;
            game::SoundSys&     soundSys_;

    };
}