#pragma once

#include "../man/GameManager.hpp"
#include "../sys/renderSys.hpp"

namespace game
{
    struct CofreSys
    {
        CofreSys(FVeng::GameManager& gameMan);
        ~CofreSys();

        CofreSys (const CofreSys&) = delete;
        CofreSys (CofreSys&&) = delete;
        CofreSys& operator=(const CofreSys&)= delete;
        CofreSys& operator=(CofreSys&&)= delete;

        //void iniPhysicsSys();
        void update();
     


        private:
            FVeng::GameManager& gMan_;

    };
}