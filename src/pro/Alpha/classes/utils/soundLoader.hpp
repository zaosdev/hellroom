#ifndef SOUNDLOADER_HPP
#define SOUNDLOADER_HPP

#include <SFML/Audio.hpp>
#include <map>


class soundLoader{
    public:
        soundLoader(){
            //carga de sonidos en buffers
            sB_player_step.loadFromFile("../resources/SFX/16_human_walk_stone_1.wav");
            sB_player_dash.loadFromFile("../resources/SFX/15_human_dash_1.wav");

            
            //agregar buffers al mapa


        }
    
        //mapa de buffers para los sonidos del juego
        std::map<std::string, sf::SoundBuffer> sBfrs; 

    private:
        sf::SoundBuffer sB_player_step;
        sf::SoundBuffer sB_player_dash;
   

};

#endif

