#pragma once

#include "../man/GameManager.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"

namespace game
{
    struct SavingSys
    {
        SavingSys(FVeng::GameManager& gameMan);
        ~SavingSys();

        SavingSys (const SavingSys&) = delete;
        SavingSys (SavingSys&&) = delete;
        SavingSys& operator=(const SavingSys&)= delete;
        SavingSys& operator=(SavingSys&&)= delete;

        //void iniPhysicsSys();
        void update();



        private:
            FVeng::GameManager& gMan_;
            sf::Clock           clock_;
            int                 saveTime_ = 5;
    };
}