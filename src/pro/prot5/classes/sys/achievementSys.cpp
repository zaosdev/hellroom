
#include "achievementSys.hpp"
#include "../man/SpriteManager.hpp"
#include <iostream>

namespace game
{
    SFMLeng::SpriteManager SPman{};
    AchievementSys::AchievementSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    AchievementSys::~AchievementSys() = default;

    /*void PhysicsSys::iniPhysicsSys()
    {
    }*/

    void AchievementSys::update(Entity& player)
    {
        int playerX = player.physics->pos.x;
        int playerY = player.physics->pos.y;

        std::cout << "posicion: " << playerX << " " << playerY << std::endl;


        if(playerX==40 && playerY==40){
            std::cout << "LOGRO DESBLOQUEADO POS=40:40" << std::endl;
            
        }       

    }
}