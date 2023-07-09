
#include "weaponSys.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"
#include "../define.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

namespace game
{
    bool can_call_function = true;

    WeaponSys::WeaponSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    WeaponSys::~WeaponSys() = default;
    
    std::chrono::steady_clock::time_point tiempo_ultima_llamada;
    std::chrono::steady_clock::time_point tiempo_comienzo_1;

    void WeaponSys::update()
    {      
        for(auto& e: gMan_.getEntityManager()){
            if(e.weapon && e.physics && e.weapon->on){
                //std::cout << "entra" << std::endl;
                auto& playerPos   = e.physics->pos;
                auto& playerSize  = e.physics->size;
                auto& sprite      = e.render->Sprite;
                FVmath::Point2D pos = {playerPos.x - 5, playerPos.y}; //little adjustement ññ
                static constexpr float adjustement = 3.f;
                pos = {(sprite.getPosition().x + sprite.getGlobalBounds().width / 2) + adjustement, sprite.getPosition().y + sprite.getGlobalBounds().height / 2};

                if(e.weapon->current!=mejora::normal){
                    auto current_time = std::chrono::steady_clock::now();
                    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - tiempo_comienzo_1).count();
                    if (elapsed_time >= 15) //<- segundo que dura un tipo d disparo especial
                    {                       
                        e.weapon->current=mejora::normal;
                        e.weapon->especial=mejora::normal;
                        elapsed_time = 0;
                    }
                }
                else{
                    //poner AQUI v condicion para activar disparos en cruz
                    if(e.weapon->especial==mejora::cruz){
                        e.weapon->current=mejora::cruz;
                        tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                    }
                    //poner AQUI v condicion para activar disparos de escopeta
                    else if(e.weapon->especial==mejora::escopeta){
                        e.weapon->current=mejora::escopeta;

                        tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                    }
                    //poner AQUI v condicion para activar disparos de rafaga
                    else if(e.weapon->especial==mejora::rafaga){
                        e.weapon->current=mejora::rafaga;

                        tiempo_comienzo_1 = std::chrono::steady_clock::now(); 
                    }
                    else{
                        e.weapon->current=mejora::normal;
                    }
                }

                //cooldown
                auto tiempo_ahora = std::chrono::steady_clock::now();
                auto tiempo_pasado = std::chrono::duration_cast<std::chrono::milliseconds>(tiempo_ahora - tiempo_ultima_llamada);
                // 1000 -> 1s
                if (tiempo_pasado.count() < 300) {
                    break;
                }
                tiempo_ultima_llamada = std::chrono::steady_clock::now();

                switch(e.weapon->direction){
                    case directionType::norte:
                        pos.y -= tileSize; 
                        switch (e.weapon->especial){
                            case mejora::escopeta:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {200,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-200,-300});

                            break;
                            case mejora::cruz:
                                pos.y -= tileSize; //generate the cross in the middle
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,0});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,0});
                            break;
                            case mejora::normal:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,-300});
                            break;
                            case mejora::rafaga:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y - 50)}, {0,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y - 100)}, {0,-300});

                            break;
                        }
                    break;
                    case directionType::sur:
                        pos.y += tileSize; 
                        switch (e.weapon->especial){
                            case mejora::normal:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,300});
                            break;
                            case mejora::escopeta:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {200,300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-200,300});

                            break;
                            case mejora::cruz:
                                pos.y -= tileSize; 
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,0});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,0});
                            break;
                            case mejora::rafaga:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,300});
                                gMan_.createBullet({int(pos.x),int(pos.y + 50)}, {0,300});
                                gMan_.createBullet({int(pos.x),int(pos.y + 100)}, {0,300});

                            break;
                        }
                    break;
                    case directionType::este:
                        pos.x += tileSize;
                        switch (e.weapon->especial){
                            case mejora::normal:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,0});
                            break;
                            case mejora::escopeta:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,0});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,200});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,-200});
                            break;
                            case mejora::cruz:
                                pos.x -= tileSize;
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,0});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,0});
                            break;
                            case mejora::rafaga:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,0});
                                gMan_.createBullet({int(pos.x + 50),int(pos.y)}, {300,0});
                                gMan_.createBullet({int(pos.x + 100),int(pos.y)}, {300,0});

                            break;
                        }
                    break;
                    case directionType::oeste:
                        pos.x -= tileSize;
                        switch (e.weapon->especial){
                            case mejora::normal:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,0});
                            break;
                            case mejora::escopeta:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,0});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,200});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,-200});

                            break;
                            case mejora::cruz:
                                pos.x += tileSize;
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,-300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {0,300});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {300,0});
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,0});
                            break;
                            case mejora::rafaga:
                                gMan_.createBullet({int(pos.x),int(pos.y)}, {-300,0});
                                gMan_.createBullet({int(pos.x - 50),int(pos.y)}, {-300,0});
                                gMan_.createBullet({int(pos.x - 100),int(pos.y)}, {-300,0});
                            break;
                        }
                    break;
                }
                e.weapon->on=false;
            }
        }
    }
}