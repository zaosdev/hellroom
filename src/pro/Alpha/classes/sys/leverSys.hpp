#pragma once

#include "../man/GameManager.hpp"
#include "../sys/soundSys.hpp"

namespace game
{
    struct LeverSys
    {
        LeverSys(FVeng::GameManager& gameMan, game::SoundSys& soundSys);
        ~LeverSys();

        LeverSys (const LeverSys&) = delete;
        LeverSys (LeverSys&&) = delete;
        LeverSys& operator=(const LeverSys&)= delete;
        LeverSys& operator=(LeverSys&&)= delete;

        //void iniPhysicsSys();
        void update();
     


        private:
            FVeng::GameManager& gMan_;
            game::SoundSys&     soundSys_;
            //game::RenderSys renSys{gMan_};
    };
}