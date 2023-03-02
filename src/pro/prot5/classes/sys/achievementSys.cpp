
#include "achievementSys.hpp"
#include "../man/SpriteManager.hpp"
#include <iostream>
#include <fstream>

namespace game
{
    AchievementSys::AchievementSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    AchievementSys::~AchievementSys() = default;
    //sf::Sprite trofeo = 

    /*void PhysicsSys::iniPhysicsSys()
    {
    }*/
    //SPman.modifyTextureRect(player.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

    void AchievementSys::update(Entity& player)
    {
        int playerX = player.physics->pos.x;
        int playerY = player.physics->pos.y;

       // std::cout << "posicion: " << playerX << " " << playerY << std::endl;


        if(playerX==40 && playerY==40){
            std::cout << "LOGRO DESBLOQUEADO POS=40:40" << std::endl;
            
        }       

    }
}