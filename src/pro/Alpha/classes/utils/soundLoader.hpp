#ifndef SOUNDLOADER_HPP
#define SOUNDLOADER_HPP

#include <SFML/Audio.hpp>
#include <map>

namespace FVSound{
    class soundLoader{
        public:
            soundLoader(){
                //carga de sonidos en buffers
                sBplayerStep.loadFromFile("../resources/SFX/16_human_walk_stone_1.wav");
                sBplayerDash.loadFromFile("../resources/SFX/15_human_dash_1.wav");

                
                //agregar buffers al mapa
                sBfrs["playerStep"] = sBplayerStep;
                sBfrs["playerDash"] = sBplayerDash;
            }
        
            //mapa de buffers para los sonidos del juego
            std::map<std::string, sf::SoundBuffer> sBfrs; 

        private:
            sf::SoundBuffer sBplayerStep;
            sf::SoundBuffer sBplayerDash;
    

    };
}

#endif

