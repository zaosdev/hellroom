
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

    void PhysicsSys::update(double dt)
    {
        auto& EM = gMan_.getEntityManager();

        for(auto& ent : EM)
        {
            if(ent.physics)
            {
                //Save the last position
                ent.physics->prevPos = ent.physics->pos;
                //Update the new position
                //collSys.update(dt);
                //ent.physics->pos+= ent.physics->vel * dt;
            }

        }        

    }
}