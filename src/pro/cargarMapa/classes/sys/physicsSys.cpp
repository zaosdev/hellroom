
#include "physicsSys.hpp"
#include <iostream>

namespace game
{
    PhysicsSys::PhysicsSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    PhysicsSys::~PhysicsSys() = default;

    void PhysicsSys::iniPhysicsSys()
    {
    }

    void PhysicsSys::update()
    {
        //std::cout << "I get here" << gMan_.ent->physics->pos.x << std::endl;

        gMan_.ent->physics->pos += gMan_.ent->physics->vel;
    }
}