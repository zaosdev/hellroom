#include "inputSys.hpp"
#include "../facade/inputFacade.hpp"

#define dash_multiplier 3
#define movement_speed  100
namespace game
{
    InputSys::InputSys(FVeng::GameManager& gameMan, InputManager& inpMan, SoundSys& soundSys, DialogueSys& dialSys)
    : gMan_(gameMan), inpRec_(inpMan), soundSys(soundSys), dialogueSys(dialSys)
    {
    }

    bool InputSys::IsGamePaused()
    {
        return gameIsPaused_;
    }

    void InputSys::unPause()
    {
        gameIsPaused_ = false;
    }

    void InputSys::update()
    {
        auto& EM = gMan_.getEntityManager();
        for(auto& ent : EM)
        {
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
                    //std::cout << "up" << std::endl;
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

            //cofre
            if(inpRec_.isKeyPressed(getKeyCode('E')))
            {
                // soundSys.setLoop(true, soundSys.soundCofre);
                // soundSys.playSound(soundSys.soundCofre, soundSys.isCofre);
                ent.cofre->abrir=true;
            }
            // else{
            //     soundSys.setLoop(false, soundSys.soundCofre);
            //     soundSys.stopSound(soundSys.soundCofre, soundSys.isCofre);
            // }

            //lever
            if(ent.hasTag(game::Entity::TAG::LEVER) && inpRec_.isKeyPressed(getKeyCode('E')))
            {
                // soundSys.setLoop(true, soundSys.soundLever);
                // soundSys.playSound(soundSys.soundLever, soundSys.isLever);
                ent.lever->pressed=true;
            }
        }

        //out of the entities things we only need to check once
        if(inpRec_.isKeyPressed(getKeyCode('e')))//e is enter in the map keys
        {
            dialogueSys.enterHasBeenPreesed();
        }

        if(inpRec_.isKeyPressed(getKeyCode('q'))) //q = quit
        {
            gameIsPaused_ = true;
        }
        cycles_++;
        if(inpRec_.isKeyPressed(getKeyCode('N')))
        {
            std::cout << cycles_ << std::endl;
            if(cycles_ > min_cycles)
            {
                gMan_.change_level=true;
                cycles_ = 0;
            }
            else
            {
                gMan_.change_level=false;
            } 
        }
    }

}

