//Sistema de sonido
 #pragma once

#include <SFML/Audio.hpp>
#include <iostream>
//#include <map>

//#include "../man/GameManager.hpp"

//namespace game{

    class SoundSys {

        public:

            //SoundSys(); /*: isPlaying(false) {}*/
            // SoundSys();
            void loadSound(const std::string& soundfile);
            void playSound();
            //void setLoop(bool loop); //repeticion del sonido al mantener la tecla 
            void stopSound();

            //std::map<sf::Keyboard::Key, SoundSys> soundMap;
            
        private: 
            sf::SoundBuffer sB;
            sf::Sound sound;
            //bool isPlaying;
    };
//}