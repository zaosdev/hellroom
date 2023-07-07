
#include "cofreSys.hpp"
#include "../sys/renderSys.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>

namespace game
{

    CofreSys::CofreSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
        first = true;
    }

    CofreSys::~CofreSys() = default;
    

    void CofreSys::update()
    {   
        if(first == true){
            std::cout <<  "COFRE!"<< std::endl;
            FVmath::Point2Di position = {210,250};
            FVmath::Point2Di position2 = {360,180};
            gMan_.createCofre(position, 1);
            //gMan_.createCofre(position2, 2);
            first = false;
        }

        game::Entity& player = gMan_.getPlayer();
        FVmath::Point2D posplayer = player.physics->pos;
        //std::cout << "pos: " << posplayer << std::endl;
        int posxPlayer = posplayer.x;
        int posyPlayer = posplayer.y;

        for(auto& e: gMan_.getEntityManager()){
            if(e.cofre && e.physics){
                //std::cout << "entra" << std::endl;
                auto& pos = e.physics->pos; //posicion cofre
                //std::cout << "pos: " << pos << std::endl;
                int posxmin = pos.x -65;
                int posxmax = pos.x +40;
                int posymin = pos.y -70;
                int posymax = pos.y +40;

                if((posxPlayer < posxmax) && (posxPlayer > posxmin) && (posyPlayer < posymax) && (posyPlayer > posymin) && (e.cofre->abrir==true) && (e.cofre->abierto == false)){
                    //std::cout << "premio!" << std::endl;
                    //std::cout << "pos: " << posplayer << std::endl;
                    //std::cout << "id: " << e.cofre->id << std::endl;
                        //premio:

                    std::srand(static_cast<unsigned int>(std::time(0)));
                    int esp = std::rand() % 3;
                    //int esp = 2;
                    if(esp==0){
                        //cruz
                        player.weapon->especial=mejora::cruz;
                        std::cout << "premio cruz" << std::endl;
                    }
                    else if(esp==1){
                        //escopeta
                        player.weapon->especial=mejora::escopeta;
                        std::cout << "premio escopeta" << std::endl;
                    }
                    else if(esp==2){
                        //rafaga
                        player.weapon->especial=mejora::rafaga;
                        std::cout << "premio rafaga" << std::endl;
                    }

                    e.cofre->abierto = true;
                }

                if(e.cofre->abrir==true){
                    //std::cout << "abrir -> true" << std::endl;
                    e.cofre->abrir=false;
                }
            }
        }
        //std::cout << "Termina el cofre sys" << std::endl;
    }
}