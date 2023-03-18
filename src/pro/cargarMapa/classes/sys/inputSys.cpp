#include "inputSys.hpp"
#include "../facade/inputFacade.hpp"

#define dash_multiplier 3
#define movement_speed  0.2
namespace game
{
    InputSys::InputSys(FVeng::GameManager& gameMan, InputManager& inpMan)
    : gMan_(gameMan), inpRec_(inpMan)
    {
    }

    void InputSys::update()
    {
        auto& EM = gMan_.getEntityManager();
        for(auto& ent : EM)
        {
            if(ent.input)
            {
                ent.physics->vel = {0,0};

                //Movement
                if(inpRec_.isKeyPressed(getKeyCode('W')))      ent.physics->vel += {0,-movement_speed}; 
                if(inpRec_.isKeyPressed(getKeyCode('A')))      ent.physics->vel += {-movement_speed,0}; 
                if(inpRec_.isKeyPressed(getKeyCode('S')))      ent.physics->vel += {0,movement_speed}; 
                if(inpRec_.isKeyPressed(getKeyCode('D')))      ent.physics->vel += {movement_speed,0}; 

                //Dash
                if(inpRec_.isKeyPressed(getKeyCode(' ')))
                {
                    ent.physics->vel.x *= dash_multiplier;
                    ent.physics->vel.y *= dash_multiplier; 
                }
            }
        }

        

    }

}

