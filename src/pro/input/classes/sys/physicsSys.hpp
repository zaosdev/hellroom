#pragma once

#include "../man/GameManager.hpp"



namespace game
{
    struct PhysicsSys
    {
        PhysicsSys(FVeng::GameManager& gameMan);
        ~PhysicsSys();

        PhysicsSys (const PhysicsSys&) = delete;
        PhysicsSys (PhysicsSys&&) = delete;
        PhysicsSys& operator=(const PhysicsSys&)= delete;
        PhysicsSys& operator=(PhysicsSys&&)= delete;

        void iniPhysicsSys();
        void update();


        private:
            FVeng::GameManager& gMan_;
    };
}