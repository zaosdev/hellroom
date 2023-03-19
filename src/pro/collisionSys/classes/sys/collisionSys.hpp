#pragma once
#include "../man/GameManager.hpp"
#include <iostream>
#include <limits>

namespace game
{

    struct CollisionSys
    {
        CollisionSys(FVeng::GameManager& gameMan);


        CollisionSys (const CollisionSys&) = delete;
        CollisionSys (CollisionSys&&) = delete;
        CollisionSys& operator=(const CollisionSys&)= delete;
        CollisionSys& operator=(CollisionSys&&)= delete;

        void update(FVeng::GameManager& gameMan);

        private:
            FVeng::GameManager& gMan_;
    
    };

}