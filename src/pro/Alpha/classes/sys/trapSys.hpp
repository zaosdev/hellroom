#pragma once

#include "../man/GameManager.hpp"
#include "../sys/renderSys.hpp"

#include <chrono>


namespace game
{
    struct TrapSys
    {
        TrapSys(FVeng::GameManager& gameMan);
        ~TrapSys();

        TrapSys (const TrapSys&) = delete;
        TrapSys (TrapSys&&) = delete;
        TrapSys& operator=(const TrapSys&)= delete;
        TrapSys& operator=(TrapSys&&)= delete;

        //void iniPhysicsSys();
        void update();
     

        private:
            FVeng::GameManager& gMan_;
            bool primera_vez = false;
            //game::RenderSys renSys{gMan_};
    };
}