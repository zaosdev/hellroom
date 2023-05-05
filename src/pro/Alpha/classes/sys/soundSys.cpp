#include "soundSys.hpp"
//#include "inputSys.hpp"
#include "../facade/inputFacade.hpp"

namespace game{

    //SoundSys::SoundSys() : isPlaying(false) {}

    SoundSys::SoundSys(FVeng::GameManager& gameMan, InputManager& inpMan): gMan_(gameMan), inpRec_(inpMan), isPlaying(false){
   
    }


    void SoundSys::loadSound(/*const std::string& soundfile*/){
        
        if(!sB.loadFromFile("../resources/SFX/16_human_walk_stone_1.wav")){
            std::cout << "SOUND FILE NOT FOUND" << std::endl;
        }
        else std::cout << "SOUND LOADED" << std::endl;
        sound.setPitch(1.5); //provisional
        sound.setBuffer(sB);

        
    }

    void SoundSys::playSound(){
       if(!isPlaying){
            sound.play();
            isPlaying = true;
        }
        std::cout << "PLAYING WALKING SOUND" << std::endl;
    }

    void SoundSys::stopSound(){
       if(isPlaying){
            sound.stop();
           isPlaying = false;
        }
    }

    void SoundSys::setLoop(bool loop){
        sound.setLoop(loop);
    }

   

    void SoundSys::update(/*SoundSys sfx*/){
   
        //Movement
            
            if(inpRec_.isKeyPressed(getKeyCode('W')) || inpRec_.isKeyPressed(getKeyCode('A')) || inpRec_.isKeyPressed(getKeyCode('S')) || inpRec_.isKeyPressed(getKeyCode('D'))) {
            //std::cout << "BOTON W" << std::endl;
         
                this->setLoop(true);
                this->playSound();
            
                //std::cout << "Sonandoooo" << std::endl;
          
        }
        else{
            this->setLoop(false);
            this->stopSound();
        }  


        //Dash
        // if(inpRec_.isKeyPressed(getKeyCode(' '))){
        //     std::cout << "BOTON SPACE" << std::endl;
        //     sfx.setLoop(false);
        //     sfx.playSound();
        // }
        // else{
        //     sfx.stopSound();
        // }

    }
}
