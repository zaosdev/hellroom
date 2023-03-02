
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

        if(x==50 && y==50){
            std::cout << "LOGRO DESBLOQUEADO POS=50:50" << std::endl;
        }       

    }
}