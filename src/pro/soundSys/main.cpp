#include <SFML/Graphics.hpp>
#include <iostream>
//#include <map>

#include "include/config.h"
#include "classes/sys/renderSys.hpp"
#include "classes/sys/physicsSys.hpp"
#include "classes/sys/inputSys.hpp"
#include "classes/sys/soundSys.hpp" //sonido
#include "classes/man/GameManager.hpp"
#include "classes/man/SpriteManager.hpp"



#define kVel 5

int main() {


  //Create Game manager
  FVeng::GameManager GameMan{640, 480,"P9. Sistema de Sonido"};

  //create Sprite manager
  //SFMLeng::SpriteManager SPman{};

  //Create Game systems
  game::RenderSys   renSys{GameMan};
  game::PhysicsSys  phySys{GameMan};
  game::InputSys    inpSys{GameMan};
  
  //puedo suponer que para que este bien hecho tengo que hacerlo igual que los otros sistemas game::SoundSys soundSys{GameMan}; ... lo probare si primero me funciona de esta manera
  SoundSys dashSound; //instancia de SoundSys
  dashSound.loadSound("resources/SFX/15_human_dash_1.wav");//cargo el archivo de audio
 
  bool isPlaying = false;

  //creo un mapa para asignar sonidos a teclas (esto seguramente deberia estar en el soundSys.cpp u otra parte)

  //auto tecla = sf::Keyboard::isKeyPressed;

  //Bucle del juego
  while (GameMan.getWindow().isOpen()) {

    sf::Event event;
    // Manejo de eventos de cerrar ventana
    while (GameMan.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            GameMan.getWindow().close();
        }
    }
   
    GameMan.getEntityManager().update();
    inpSys.update();
    phySys.update();

    

    // for(auto const& pair:soundMap){
    //   if(sf::Keyboard::isKeyPressed(pair.first)){
    //     pair.second.playSound();
    //   }
    // }

    //esto seguramente deberia estar en un inputManager...
    //de momento lo hago a lo cutre

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      if(!isPlaying){
        dashSound.playSound();
        isPlaying = true;
        std::cout << "Sonandoooo" << std::endl;
      }
    }
    else{
      isPlaying = false;
    }

    // if(tecla(sf::Keyboard::A) || tecla(sf::Keyboard::D) || tecla(sf::Keyboard::W) || tecla(sf::Keyboard::S)) {
    //   //if(!isPlaying){
    //     moveSound.playSound();
    //     //isPlaying = true;
        
      
    // }
    // else{
    //   isPlaying = false;
    // }
    
    renSys.update();


    // while (GameMan.getWindow().pollEvent(event)) {
    //     if (event.type == sf::Event::Closed) {
    //         GameMan.getWindow().close();
    //     }
    // }
   
    //sf::sleep(sf::milliseconds(20));
  }
  return 0;
}