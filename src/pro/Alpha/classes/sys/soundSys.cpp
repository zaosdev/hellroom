#include "soundSys.hpp"
#include "../facade/inputFacade.hpp"

namespace game{

    //SoundSys::SoundSys() : isPlaying(false) {}

    SoundSys::SoundSys(FVeng::GameManager& gameMan, InputManager& inpMan): gMan_(gameMan), inpRec_(inpMan), isPlaying(false){
   
    }


    void SoundSys::loadSounds(/*const std::string& soundfile*/){

        
        loadSound("playerStep","../resources/SFX/16_human_walk_stone_1.wav");
        loadSound("playerDash","../resources/SFX/15_human_dash_1.wav");

        // sf::SoundBuffer sB;
        
        // if(!sB.loadFromFile("../resources/SFX/16_human_walk_stone_1.wav")){
        //     std::cout << "SOUND FILE NOT FOUND" << std::endl;
        // }
        // else std::cout << "SOUND LOADED" << std::endl;
        // soundP.setPitch(1.5); //provisional
        // soundP.setBuffer(sB);


        
    }

    void SoundSys::loadSound(const std::string& skey, const std::string& soundpath){

        sf::SoundBuffer buffer;

         if (buffer.loadFromFile(soundpath)) {
            sBfrs[skey] = buffer;
            
            soundP.setPitch(1.5); //esto acelera la reproduccion de sonido
            soundP.setBuffer(sBfrs["playerStep"]); //asigno el sonido que necesito
        }

    }

    void SoundSys::playSound(sf::Sound& sound){
        
        //  if(sBfrs.count(skey)>0){
        //      sound.setBuffer(sBfrs[skey])

            

            if(!isPlaying){
                std::cout << "PLAYING WALKING SOUND" << std::endl;
                sound.play();
                isPlaying = true;
            }
        
            
        
    }

    void SoundSys::stopSound(sf::Sound& sound){
       if(isPlaying){
            sound.stop();
           isPlaying = false;
        }
    }

    void SoundSys::setLoop(bool loop, sf::Sound& sound){
        sound.setLoop(loop);
    }

   

    void SoundSys::update(/*SoundSys sfx*/){
   
        //Movement
            
            if(inpRec_.isKeyPressed(getKeyCode('W')) || inpRec_.isKeyPressed(getKeyCode('A')) || inpRec_.isKeyPressed(getKeyCode('S')) || inpRec_.isKeyPressed(getKeyCode('D'))) {
            //std::cout << "BOTON W" << std::endl;
            
            //sound.setPitch(1.5); //provisional
                
              //  soundP.setBuffer(sB);
                // sound.setPitch(1.5);
                // sound.setBuffer(sBfrs["playerStep"]);
               
                this->setLoop(true, soundP);
                this->playSound(soundP); //procedo a asignar un buffer para reproducir el sonido solicitado
                
                //this->playSound();

                
                //std::cout << "Sonandoooo" << std::endl;
          
        }
        else{
            this->setLoop(false, soundP);
            this->stopSound(soundP);
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
