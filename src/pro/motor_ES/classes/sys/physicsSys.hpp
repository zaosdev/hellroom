#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"



namespace game
{
    struct PhysicsSys
    {
        PhysicsSys(FVeng::GameManager& gameMan);
        ~PhysicsSys();

        void iniPhysicsSys();
        void update();


        private:
            FVeng::GameManager& gMan_;
            Entity ent;
    };
}