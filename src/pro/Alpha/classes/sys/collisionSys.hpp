#pragma once

#include "../man/GameManager.hpp"



namespace game
{
    struct CollisionSys
    {
        CollisionSys(FVeng::GameManager& gameMan);
        ~CollisionSys();

        CollisionSys (const CollisionSys&) = delete;
        CollisionSys (CollisionSys&&) = delete;
        CollisionSys& operator=(const CollisionSys&)= delete;
        CollisionSys& operator=(CollisionSys&&)= delete;

        //void iniPhysicsSys();
        void update(); //gestionara las colisiones


        private:
            FVeng::GameManager& gMan_;
    };
}