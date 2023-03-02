
#include "achievementSys.hpp"
#include <iostream>

namespace game
{
    AchievementSys::AchievementSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    AchievementSys::~AchievementSys() = default;

    /*void PhysicsSys::iniPhysicsSys()
    {
    }*/

    void AchievementSys::check(int x, int y)
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