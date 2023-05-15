#include "petSys.hpp"
#include <iostream>


namespace game
{
    PetSys::PetSys(FVeng::GameManager& gameMan, game::ShieldSys& shieldSys)
    : gMan_(gameMan)
    , ssys_(shieldSys)
    {
    }

    PetSys::~PetSys() = default;

    void PetSys::initPetSys()
    {
        petNum_ = FVData::getSelectedPet();
    }

    void PetSys::update(double dt)
    {
        if(petNum_ == -1) return;

        auto& EM = gMan_.getEntityManager();
        totalTime_ += dt;

        for(auto& ent : EM)
        {
            
            if(ent.physics && ent.hasTag(Entity::TAG::Pet))
            {
                //Save the last position
                ent.physics->prevPos = ent.physics->pos;

                //Update the new position using a sin and cos
                float x = amplitude * sin(frequency * totalTime_);
                float y = amplitude * cos(frequency * totalTime_);

                //Get the player and its position to follow him
                auto& player = gMan_.getPlayer();
                auto& playerPosition = player.physics->pos;

                ent.physics->pos  = playerPosition + FVmath::Point2D{displacement_x + x, displacement_y + y};

                switch (petNum_)
                {
                    case 0: //vitalis
                        player.health->positiveAffection = 0.5;
                        ent.health->positiveAffection    = 0.1;
                        break;
                    case 1: //guardian
                        if(ent.shield->active)
                        {
                            //std::cout << "el escudo de la mascota esta activo.... " << std::endl;
                            ssys_.activateShield(player, false);
                        }
                        //else  std::cout << "el escudo de la mascota NOOOOOOOO esta activo.... " << std::endl;
                        break;
                    case 2: //sentinel

                        break;
                    default:
                        break;
                }
            }

        }        

    }
}