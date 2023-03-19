//Sistema de sonido
#pragma once
#include "../man/GameManager.hpp"
#include "../man/inputManager.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>




namespace game{

    struct SoundSys {

        // public:

            //SoundSys(); /*: isPlaying(false) {}*/
            SoundSys(FVeng::GameManager& gameMan, InputManager& intpRec);

            // SoundSys (const SoundSys&) = delete;
            // SoundSys (SoundSys&&) = delete;
            // SoundSys& operator=(const SoundSys&)= delete;
            // SoundSys& operator=(SoundSys&&)= delete;


            void loadSound(const std::string& soundfile);
            void playSound();
            void setLoop(bool loop); //repeticion del sonido al mantener la tecla 
            void stopSound();

            void update(/*SoundSys sfx*/); // reproducira sonidos segun la tecla pulsada
            
            // void asignSound();

            //std::map<sf::Keyboard::Key, SoundSys> soundMap;
            
        private: 
            FVeng::GameManager& gMan_;
            InputManager&       inpRec_;

            sf::SoundBuffer sB;
            sf::Sound sound;


            bool isPlaying;
            std::map<sf::Keyboard::Key, SoundSys> soundMap;
    };
}