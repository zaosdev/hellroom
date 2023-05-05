//Sistema de sonido
#pragma once
#include "../man/GameManager.hpp"
#include "../man/inputManager.hpp"
#include "../utils/soundLoader.hpp"
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
            void playSound(); 
            void setLoop(bool loop); //repeticion del sonido al mantener la tecla 
            void stopSound();

            void update(); // reproducira sonidos segun la tecla pulsada
    
            // sound por entidad --> player, enemy, bullet player, bullet enemy
            sf::Sound soundP;
            sf::Sound soundE;
            sf::Sound soundBP;
            sf::Sound soundBF;
            
        private: 
            FVeng::GameManager& gMan_;
            InputManager&       inpRec_;
            bool isPlaying;
            
    };
}