#include "soundSys.hpp"
#include "../facade/inputFacade.hpp"

namespace game{

    //SoundSys::SoundSys() : isPlaying(false) {}

    SoundSys::SoundSys(FVeng::GameManager& gameMan, InputManager& inpMan): gMan_(gameMan), inpRec_(inpMan){
        
        isPlayingStep = false;
        isPlayingDash = false;


        //musicPlaying = false;
   
    }


    void SoundSys::loadSounds(/*const std::string& soundfile*/){

        
        // loadSound("playerStep","../resources/SFX/16_human_walk_stone_1.wav");
        // loadSound("playerDash","../resources/SFX/15_human_dash_1.wav");
        if(!sBplayerStep.loadFromFile("../media/SFX/16_human_walk_stone_1.wav")){std::cout << "FAILED TO LOAD PLAYERSTEP" << std::endl; }
        if(!sBplayerDash.loadFromFile("../media/SFX/15_human_dash_1.wav")){std::cout << "FAILED TO LOAD PLAYERDASH" << std::endl; }

        // sBfrs["playerStep"] = sBplayerStep;
        // sBfrs["playerDash"] = sBplayerDash;

        soundP.setPitch(1.5); //esto acelera la reproduccion de sonido
        soundP.setBuffer(sBplayerStep); //asigno el sonido que necesito
        
        soundD.setPitch(1.5);
        soundD.setBuffer(sBplayerDash);


        if (!music.openFromFile("../media/MUSIC/OST-Juego.wav")) {
            std::cout << "FAILED TO LOAD MUSIC" << std::endl;
        
        } 
        else {
            music.setVolume(25); 
            music.setLoop(true); 
            
        }

        
    }


    void SoundSys::playSound(sf::Sound& sound, bool& isPlaying){
        
            if(!isPlaying){
               // std::cout << "PLAYING WALKING SOUND" << std::endl;
                sound.play();
                isPlaying = true;
            }

    }

    void SoundSys::stopSound(sf::Sound& sound, bool& isPlaying){
       if(isPlaying){
            sound.stop();
           isPlaying = false;
        }
    }

    void SoundSys::setLoop(bool loop, sf::Sound& sound){
        sound.setLoop(loop);
    }



     void SoundSys::playMusic(){
        
        if (!musicPlaying) {
            std::cout << "PLAYING MUSIC" << std::endl;
            music.play();
            musicPlaying = true;
        }
    }

    void SoundSys::stopMusic(){
        
        if (musicPlaying) {
            music.stop();
            musicPlaying = false;
        }
    }
   

    void SoundSys::update(/*SoundSys sfx*/){
   
        //Movement
            
        if(inpRec_.isKeyPressed(getKeyCode('W')) || inpRec_.isKeyPressed(getKeyCode('A')) || inpRec_.isKeyPressed(getKeyCode('S')) || inpRec_.isKeyPressed(getKeyCode('D'))) {
        //std::cout << "BOTON W" << std::endl;
            
            this->setLoop(true, soundP);
            this->playSound(soundP, isPlayingStep); //procedo a asignar un buffer para reproducir el sonido solicitado
  
        }
        else{
            this->setLoop(false, soundP);
            this->stopSound(soundP,  isPlayingStep);
        }  


        //Dash
        if(inpRec_.isKeyPressed(getKeyCode(' '))){
            //std::cout << "BOTON SPACE" << std::endl;
            this->setLoop(false, soundD);
            this->playSound(soundD,  isPlayingDash);
        }
        else{
            this->stopSound(soundD,  isPlayingDash);
        }


         // Play/Stop music
        if (inpRec_.isKeyPressed(getKeyCode('M'))) {
            if (musicPlaying) {
                this->stopMusic();
            } else {
                this->playMusic();
            }
        }

    }
}
