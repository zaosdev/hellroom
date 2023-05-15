#ifndef SOUNDLOADER_HPP
#define SOUNDLOADER_HPP

#include <SFML/Audio.hpp>
#include <map>

namespace FVSound{
    class soundLoader{
        public:
            soundLoader(){
                //carga de sonidos en buffers
                if(!sBplayerStep.loadFromFile("../resources/SFX/16_human_walk_stone_1.wav")){
                   // std::cout << "FAILED TO LOUD SOUND: STEPS" <<  std::endl;
                }
                if(!sBplayerDash.loadFromFile("../resources/SFX/15_human_dash_1.wav")){
                   // std::cout << "FAILED TO LOUD SOUND: DASH" <<  std::endl;
                }
                
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

