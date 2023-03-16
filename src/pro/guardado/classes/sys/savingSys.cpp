
#include "savingSys.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"
#include <iostream>
#include <fstream>

namespace game
{
    SavingSys::SavingSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    SavingSys::~SavingSys() = default;
    //sf::Sprite trofeo = 

    /*void PhysicsSys::iniPhysicsSys()
    {
    }*/

    std::array<int, 2> SavingSys::read(){
        std::string cadena;
        int posX = -1;
        int posY = -1;
        std::string file = "/home/osboxes/Desktop/repositorio abp/proyecto-abp-grupo-j4/src/pro/guardado/estado.txt";
        std::ifstream archivoL(file);
        while (getline (archivoL, cadena)){
            std::string posicionXstring = cadena.substr(0, cadena.find(","));
            cadena.erase(0, cadena.find(",") + 1);
            std::string posicionYstring = cadena.substr(0, cadena.find(","));
            posX = stoi(posicionXstring);
            posY = stoi(posicionYstring);
        }
        if(posX==-1 && posY==-1){
            posX = 320;
            posY = 240;
        }
        std::array<int, 2> pos;
        pos[0] = posX;
        pos[1] = posY;
        return pos;
    }
    

    void SavingSys::update(Entity& player)
    {
        int playerX = player.physics->pos.x;
        int playerY = player.physics->pos.y;

        std::string file = "/home/osboxes/Desktop/repositorio abp/proyecto-abp-grupo-j4/src/pro/guardado/estado.txt";
        std::ifstream archivoL(file);
        /*while (getline (archivoL, cadena)){
            //leer
        }*/
        //escribir
        std::ofstream archivoE(file);
        archivoE << playerX << "," << playerY << std::endl;
        archivoE.close();
           
              

    }
}