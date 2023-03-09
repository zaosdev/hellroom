
#include "achievementSys.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"
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
    void AchievementSys::showPic(){
        
        sf::Sprite img;// = SPman.SpriteManager();
        //SPman.modifyTextureRect(player.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));
        SPman.loadTexture(img.setTexture(),"/home/osboxes/Desktop/repositorio abp/proyecto-abp-grupo-j4/src/pro/prot5/logros.png");
        //Y creo el spritesheet a partir de la imagen anterior
        SPman.assignTexture(img.Sprite,img.tex);
    }

    void AchievementSys::update(Entity& player)
    {
        int playerX = player.physics->pos.x;
        int playerY = player.physics->pos.y;

       // std::cout << "posicion: " << playerX << " " << playerY << std::endl;


        if(playerX==40 && playerY==40){
            
            //logro 0, posicion (40,40)
            bool unlocked = false;
            std::string cadena;
            std::string file = "/home/osboxes/Desktop/repositorio abp/proyecto-abp-grupo-j4/src/pro/prot5/logros-desbloqueados.txt";
            std::ifstream archivoL(file);
            while (getline (archivoL, cadena)){
                if(cadena == "0"){
                    unlocked = true;
                }
            }
            if(unlocked == false){
                std::cout << "LOGRO DESBLOQUEADO POS=40:40" << std::endl;
                //enseñar logro.png duranto 3 segundos
                std::ofstream archivoE(file);
                archivoE << "0" << std::endl;
                archivoE.close();
            }
           
        }       

    }
}