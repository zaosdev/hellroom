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
        if(primera_vez == false){
            FVmath::Point2Di Pos = {150,150};
            tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
            gMan_.createTrap(Pos);
            primera_vez = true;
            std::cout << "estado 0" << std::endl;

        }

        for(auto& e: gMan_.getEntityManager()){
            if(e.trap){
                auto current_time = std::chrono::steady_clock::now();
                auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - tiempo_comienzo_1).count();
                if (elapsed_time >= e.trap->delayTime) { //<- segundos que dura cada estado de la trampa

                    if(e.trap->modo==estado::primero){
                        e.trap->modo=estado::segundo;
                        tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                        //Cambiar imagen de la trampa
                        std::cout << "estado 1" << std::endl;
                    }
                    else if(e.trap->modo==estado::segundo){
                        e.trap->modo=estado::tercero;
                        tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                        //Cambiar imagen de la trampa
                        std::cout << "estado 2" << std::endl;

                    }
                    else if(e.trap->modo==estado::tercero){
                        e.trap->modo=estado::cuarto;
                        //Cambiar imagen de la trampa
                        std::cout << "estado 3" << std::endl;
                    }
                }
                if(e.trap->modo==estado::cuarto){
                    //Comprobar si el jugador esta en la posicion de la trampa, mediante un rando de esta misma. SI se encuentra, se le resta vida, se cambiara la imagen y se resetea el tiempo. 
                    //Hacer que la tarampa este por detras del jugador, ver como se cambian las imagenes y mirar que funciona el contador.
                    std::cout << "estado 4" << std::endl;
                }
            }
        }

    }
}