#include "trapSys.hpp"
#include "../sys/renderSys.hpp"

#include <iostream>
#include <fstream>
#include <thread>

namespace game
{

    TrapSys::TrapSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    TrapSys::~TrapSys() = default;

    void TrapSys::update()
    {  

        for(auto& e: gMan_.getEntityManager()){
            if(e.trap){
                e.trap->current_time = std::chrono::steady_clock::now();
                e.trap->elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(e.trap->current_time - e.trap->tiempo_comienzo_1).count();
                if (e.trap->elapsed_time >= e.trap->delayTime) { //<- segundos que dura cada estado de la trampa

                    if(e.trap->modo==estado::primero){
                        e.trap->modo=estado::segundo;
                        e.trap->tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                        gMan_.initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(2*gMan_.getMapManager().getTileSize().x,11*gMan_.getMapManager().getTileSize().y, 16, 16));

                        //std::cout << "estado 1" << std::endl;
                    }
                    else if(e.trap->modo==estado::segundo){
                        e.trap->modo=estado::tercero;
                        e.trap->tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                        gMan_.initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(3*gMan_.getMapManager().getTileSize().x,11*gMan_.getMapManager().getTileSize().y, 16, 16));
                        //std::cout << "estado 2" << std::endl;

                    }
                    else if(e.trap->modo==estado::tercero){
                        e.trap->modo=estado::cuarto;
                        e.trap->tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                        gMan_.initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(4*gMan_.getMapManager().getTileSize().x,11*gMan_.getMapManager().getTileSize().y, 16, 16));
                        //std::cout << "estado 3" << std::endl;
                    }
                    else if(e.trap->modo==estado::cuarto){
                        e.trap->modo=estado::primero;
                        e.trap->tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                        gMan_.initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(1*gMan_.getMapManager().getTileSize().x,11*gMan_.getMapManager().getTileSize().y, 16, 16));
                        //std::cout << "estado 4" << std::endl;
                    }
                }
                
            }
        }

    }
}