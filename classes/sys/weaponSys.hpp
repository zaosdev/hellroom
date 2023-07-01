#pragma once

#include "../man/GameManager.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"

namespace game
{
    struct WeaponSys
    {
        WeaponSys(FVeng::GameManager& gameMan);
        ~WeaponSys();

        WeaponSys (const WeaponSys&) = delete;
        WeaponSys (WeaponSys&&) = delete;
        WeaponSys& operator=(const WeaponSys&)= delete;
        WeaponSys& operator=(WeaponSys&&)= delete;

        //void iniPhysicsSys();
        void update();
     


        private:
            FVeng::GameManager& gMan_;
            //game::RenderSys renSys{gMan_};
    };
}