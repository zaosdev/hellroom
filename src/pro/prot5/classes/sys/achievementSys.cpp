
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

    void AchievementSys::update(int x, int y)
    {
        std::cout << "posicion: " << x << " " << y << std::endl;
        auto& EM = gMan_.getEntityManager();

        if(x==40 && y==40){
            std::cout << "LOGRO DESBLOQUEADO POS=50:50" << std::endl;
            
        }       

    }
}