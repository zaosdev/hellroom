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
            void loadSound(const std::string& skey, const std::string& soundpath);
            void playSound(sf::Sound& sound); 
            void setLoop(bool loop, sf::Sound& sound); //repeticion del sonido al mantener la tecla 
            void stopSound(sf::Sound& sound);

            void update(); // reproducira sonidos segun la tecla pulsada
    
            // sound por entidad --> player, enemy, bullet player, bullet enemy
            //FVSound::soundLoader sounds;
            sf::Sound sound;
            sf::Sound soundP;
            sf::Sound soundE;
            sf::Sound soundBP;
            sf::Sound soundBF;
            
        private: 
            std::map<std::string, sf::SoundBuffer> sBfrs; 
            FVeng::GameManager& gMan_;
            InputManager&       inpRec_;
            bool isPlaying;
            
    };
}