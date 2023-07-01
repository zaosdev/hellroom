#include "shieldSys.hpp"

#define dash_multiplier 3
#define movement_speed  100

namespace game
{
    ShieldSys::ShieldSys(FVeng::GameManager& gameMan, InputManager& inpMan)
    : gMan_(gameMan), inpRec_(inpMan)
    {
    }

    void ShieldSys::update(double dt)
    {
        auto& EM = gMan_.getEntityManager();
        for(auto& ent : EM)
        {
            if(ent.shield)
            {
                if(not (ent.shield->active))
                {   
                    check4Activation(ent, dt);
                    ent.shield->activatedTime = 0;
                }
                else
                {
                    activatedLogic(ent, dt);
                }
                
            }
        }
    }


    void ShieldSys::activateShield(game::Entity& ent, bool restartTime)
    {
        if (restartTime) 
        {
            ent.shield->passedTime = 0;
        }
        ent.shield->active = true;
    }

    void ShieldSys::check4Activation(game::Entity& ent, double dt)
    {
        ent.shield->passedTime += dt;

            //check if time passed
            if(ent.shield->passedTime > ent.shield->refreshTime)
            {
                //check if is auto active and then active
                if(ent.shield->autoActive)
                {
                    activateShield(ent, true);
                } 
                else
                {
                    //if not auto active, active only when the key is pressed
                    if(inpRec_.isKeyPressed(getKeyCode(SHIELD_KEY)))
                    {
                        activateShield(ent, true);
                    }
                }
            }
    }

    void  ShieldSys::activatedLogic(game::Entity& ent, double dt)
    {
        ent.shield->activatedTime += dt;
        if(ent.shield->activatedTime > ent.shield->max_ActivatedTime)
        {
            ent.shield->active = false;
        }
    }

 
} //namespace game 

