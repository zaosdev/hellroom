#include "soundSys.hpp"
#include "../facade/inputFacade.hpp"

namespace game{

    //SoundSys::SoundSys() : isPlaying(false) {}

    SoundSys::SoundSys(FVeng::GameManager& gameMan, InputManager& inpMan): gMan_(gameMan), inpRec_(inpMan){
       
        initMusic = true; //musica reproduciendose nada mas entrar al nivel
       
        isPlayingStep = false;
        isPlayingDash = false;
        isPlayingPB   = false;
        isPHit        = false;

        isMdown       = false;
        isMup         = false;

        isGameOver    = false;

        isEHit        = false;
        isEShoot      = false;

        
        isChangeLvl   = false;

        isCofre       = false;
        isLever       = false;
        isHeart       = false;


        musicPlaying = false;
   
    }


    void SoundSys::loadSounds(/*const std::string& soundfile*/){

        
        // loadSound("playerStep","../media/SFX/16_human_walk_stone_1.wav");
        // loadSound("playerDash","../media/SFX/15_human_dash_1.wav");

        //PLAYER SOUNDS
        if(!sBplayerStep.loadFromFile("../media/SFX/16_human_walk_stone_1.wav")){std::cout << "FAILED TO LOAD PLAYERSTEP" << std::endl; }
        if(!sBplayerDash.loadFromFile("../media/SFX/15_human_dash_1.wav")){std::cout << "FAILED TO LOAD PLAYERDASH" << std::endl; }
        if(!sBplayerBullet.loadFromFile("../media/SFX/Laser_Shoot2.wav")){std::cout << "FAILED TO LOAD PLAYERBULLET" << std::endl;}
        if(!sBplayerHit.loadFromFile("../media/SFX/hit_player.wav")){std::cout << "FAILED TO LOAD PLAYERHIT" << std::endl;}

        if(!sBMdown.loadFromFile("../media/SFX/Blip_Select3.wav")){std::cout << "FAILED TO LOAD MENU DOWN" << std::endl;}
        if(!sBMup.loadFromFile("../media/SFX/Blip_Select4.wav")){std::cout << "FAILED TO LOAD MENU UP" << std::endl;}

        // //GAME OVER
        // if(!sBGameOver.loadFromFile(".../media/SFX/game_over.wav")){std::cout << "FAILED TO LOAD GAMEOVER" << std::endl;}

        //ENEMY SOUNDS
        if(!sBenemyHit.loadFromFile("../media/SFX/hit_enemy.wav")){std::cout << "FAILED TO LOAD ENEMYHIT" << std::endl;}
        if(!sBenemyShoot.loadFromFile("../media/SFX/shoot_enemy.wav")){std::cout << "FAILED TO LOAD ENEMYSHOOT" << std::endl;}


        //CHANGE LEVEL
        if(!sBchangeLevel.loadFromFile("../media/SFX/changeLVL.wav")){std::cout << "FAILED TO LOAD CHANGE LEVEL" << std::endl;}


        //COFRE Y PALANCA
        if(!sBcofre.loadFromFile("../media/SFX/cofre.wav")){std::cout << "FAILED TO LOAD COFRE" << std::endl;}
        if(!sBlever.loadFromFile("../media/SFX/palanca.wav")){std::cout << "FAILED TO LOAD PALANCA" << std::endl;}
        if(!sBHeart.loadFromFile("../media/SFX/heart.wav")){std::cout << "FAILED TO LOAD HEART" << std::endl;}


        // sBfrs["playerStep"] = sBplayerStep;
        // sBfrs["playerDash"] = sBplayerDash;

        soundP.setPitch(1.5); //esto acelera la reproduccion de sonido
        soundP.setBuffer(sBplayerStep); //asigno el sonido que necesito
        soundD.setPitch(1.5);
        soundD.setBuffer(sBplayerDash);
        soundPbullet.setVolume(20);
        soundPbullet.setBuffer(sBplayerBullet);
        soundPHit.setPitch(0.5);
        soundPHit.setBuffer(sBplayerHit);

        soundGameOver.setBuffer(sBGameOver);

        soundEHit.setVolume(20);
        soundEHit.setPitch(1.5);
        soundEHit.setBuffer(sBenemyHit);
        soundEShoot.setVolume(20);
        soundEShoot.setPitch(0.5);
        soundEShoot.setBuffer(sBenemyShoot);

        //soundLevel.setVolume(75);
        soundLevel.setBuffer(sBchangeLevel); // comprobar por que no suena

        soundCofre.setBuffer(sBcofre);
        soundLever.setBuffer(sBlever);
        soundHeart.setBuffer(sBHeart);


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
            music.pause();
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
        if(initMusic == true){ 
            this->playMusic();
            initMusic = false;
        }
        if (inpRec_.isKeyPressed(getKeyCode('M'))) {
            if (musicPlaying) {
                this->stopMusic();
            } else {
                this->playMusic();
            }
        }

    }
}
