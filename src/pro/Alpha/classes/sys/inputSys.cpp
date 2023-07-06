#include "inputSys.hpp"
#include "../facade/inputFacade.hpp"

#define dash_multiplier 3
#define movement_speed  100
namespace game
{
    InputSys::InputSys(FVeng::GameManager& gameMan, InputManager& inpMan, SoundSys& soundSys)
    : gMan_(gameMan), inpRec_(inpMan), soundSys(soundSys)
    {
    }

    void InputSys::update()
    {
        auto& EM = gMan_.getEntityManager();
        for(auto& ent : EM)
        {
            if(inpRec_.isKeyPressed(getKeyCode('N')))   gMan_.change_level=true; 


            if(ent.input && ent.physics)
            {
                ent.physics->vel = {0,0};
                auto speedmov = ent.physics->mov_speed;

                //Movement
                if(inpRec_.isKeyPressed(getKeyCode('W')))      ent.physics->vel += {0,-speedmov}; 
                if(inpRec_.isKeyPressed(getKeyCode('A')))      ent.physics->vel += {-speedmov,0}; 
                if(inpRec_.isKeyPressed(getKeyCode('S')))      ent.physics->vel += {0,speedmov}; 
                if(inpRec_.isKeyPressed(getKeyCode('D')))      ent.physics->vel += {speedmov,0}; 

                //Dash
                if(inpRec_.isKeyPressed(getKeyCode(' ')))
                {
                    ent.physics->vel.x *= dash_multiplier;
                    ent.physics->vel.y *= dash_multiplier; 
                }

                if(inpRec_.isKeyPressed(getKeyCode('1')))
                {
                    ent.weapon->especial=mejora::cruz;
                }
                if(inpRec_.isKeyPressed(getKeyCode('2')))
                {
                    ent.weapon->especial=mejora::escopeta;
                }
                if(inpRec_.isKeyPressed(getKeyCode('3')))
                {
                    ent.weapon->especial=mejora::rafaga;
                }
            }

            //bullet

            if(inpRec_.isKeyPressed(getKeyCode('u'))|| inpRec_.isKeyPressed(getKeyCode('d')) || inpRec_.isKeyPressed(getKeyCode('l')) || inpRec_.isKeyPressed(getKeyCode('r'))){

                soundSys.setLoop(true, soundSys.soundPbullet);
                soundSys.playSound(soundSys.soundPbullet, soundSys.isPlayingPB);

                if(inpRec_.isKeyPressed(getKeyCode('u'))){
                    std::cout << "up" << std::endl;
                     ent.weapon->on=true; 
                     ent.weapon->direction=directionType::norte;
    
                }    
                if(inpRec_.isKeyPressed(getKeyCode('d'))){
                     ent.weapon->on=true; 
                     ent.weapon->direction=directionType::sur;
                }     
                if(inpRec_.isKeyPressed(getKeyCode('l'))){
                     ent.weapon->on=true; 
                     ent.weapon->direction=directionType::oeste;
                }     
                if(inpRec_.isKeyPressed(getKeyCode('r'))){
                     ent.weapon->on=true; 
                     ent.weapon->direction=directionType::este;
                }   
            }
            else soundSys.stopSound(soundSys.soundPbullet, soundSys.isPlayingPB);

                
        }

        

    }

}

