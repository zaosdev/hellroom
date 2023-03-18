
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
        auto& EM = gMan_.getEntityManager();

        for(auto& ent : EM)
        {
            if(ent.physics)
            {
                std::cout << "do get here" << ent.physics->pos.x << std::endl;
                ent.physics->pos += ent.physics->vel;
            }

        }        

    }
}