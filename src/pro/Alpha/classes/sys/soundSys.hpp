//Sistema de sonido
#pragma once
#include "../man/GameManager.hpp"
#include "../man/inputManager.hpp"
#include <SFML/Audio.hpp>
//#include "../utils/soundLoader.hpp"
#include <iostream>
#include <map>

namespace game{

    struct SoundSys {

        // public:

            //SoundSys(); /*: isPlaying(false) {}*/
            SoundSys(FVeng::GameManager& gameMan, InputManager& intpRec);

            SoundSys (const SoundSys&) = delete;
            SoundSys (SoundSys&&) = delete;
            SoundSys& operator=(const SoundSys&)= delete;
            SoundSys& operator=(SoundSys&&)= delete;

            void loadSounds(/*const std::string& soundfile*/); //cargara todos los sonidos del juego en buffers
            //void loadSound(const std::string& skey, const std::string& soundpath);
            void playSound(sf::Sound& sound, bool& isPlaying); 
            void setLoop(bool loop, sf::Sound& sound); //repeticion del sonido al mantener la tecla 
            void stopSound(sf::Sound& sound,  bool& isPlaying);

            void playMusic();
            void stopMusic();

            void update(); // reproducira sonidos segun la tecla pulsada
    
            // sound por entidad --> player, enemy, bullet player, bullet enemy
            //FVSound::soundLoader sounds;

           // std::map<std::string, sf::SoundBuffer> sBfrs; 
            
            //BUFFERS
            sf::SoundBuffer sBplayerStep;
            sf::SoundBuffer sBplayerDash;
            sf::SoundBuffer sBplayerBullet;
            sf::SoundBuffer sBplayerHit;

            sf::SoundBuffer sBGameOver;

            sf::SoundBuffer sBMdown;
            sf::SoundBuffer sBMup;

            sf::SoundBuffer sBenemyHit;
            sf::SoundBuffer sBenemyShoot;

            sf::SoundBuffer sBchangeLevel;

            sf::SoundBuffer sBcofre;
            sf::SoundBuffer sBlever;
            sf::SoundBuffer sBHeart;


            //SOUNDS
            //Player Sounds
            sf::Sound soundP;
            sf::Sound soundD;
            sf::Sound soundPbullet;
            sf::Sound soundPHit;

            //Game Over
            sf::Sound soundGameOver;

            //Main Menu
            sf::Sound soundMdown;
            sf::Sound soundMup;

            //Enemy Sounds
            sf::Sound soundEHit;
            sf::Sound soundEShoot;

            //Change Level
            sf::Sound soundLevel;

            //Cofre , Palanca y Heart
            sf::Sound soundCofre;
            sf::Sound soundLever;
            sf::Sound soundHeart;

            // sf::Sound soundBP;
            // sf::Sound soundBF;
            sf::Music music;
            bool isPlayingStep, isPlayingDash, isPlayingPB, isPHit;
            bool musicPlaying, initMusic;

            bool isGameOver;

            bool isMdown, isMup; //main menu 

            bool isEHit, isEShoot;

            bool isChangeLvl;

            bool isCofre, isLever, isHeart;


            
        private: 
            
            FVeng::GameManager& gMan_;
            InputManager&       inpRec_;

            //sf::Music music;

            
            
    };
}