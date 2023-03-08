#include <SFML/Graphics.hpp>
#include <iostream>

#include <fstream>
#include <string>

#include "include/config.h"
#include "classes/sys/renderSys.hpp"
#include "classes/sys/physicsSys.hpp"
#include "classes/sys/inputSys.hpp"
#include "classes/man/GameManager.hpp"
#include "classes/man/SpriteManager.hpp"



#define kVel 5

int main() {


  //Create Game manager
  FVeng::GameManager GameMan{640, 480,"P2. Cuadro de Texto"};

  //create Sprite manager
  //SFMLeng::SpriteManager SPman{};

  //Create Game systems
  game::RenderSys   renSys{GameMan};
  game::PhysicsSys  phySys{GameMan};
  game::InputSys    inpSys{GameMan};


  //auto& EM = GameMan.getEntityManager();


//para que salga el texto en pantalla necesito un obj texto
  sf::Font fuente;
  fuente.loadFromFile("resources/Minecraft.ttf"); //fuente con la que se vera el texto

  sf::Text texto("", fuente, 16);
  texto.setFillColor(sf::Color::Yellow);
  texto.setPosition(10,10);

  //  // Cargamos el sprite de cuadro de texto
  // sf::Texture texture;
  // texture.loadFromFile("resources/cuadro_texto.png");
  // sf::Sprite cuadro(texture);

  //Creamos un cuadro para el texto
  sf::RectangleShape cuadro(sf::Vector2f((GameMan.getWindow().getSize().x - 20), 100));
  cuadro.setPosition(5,5);
  cuadro.setOutlineThickness(3);
  cuadro.setOutlineColor(sf::Color::Blue);
  cuadro.setFillColor(sf::Color::Transparent);
  
  std::ifstream leer("resources/texto.txt");
  std::string linea;


  bool skip = false; //para saber si se lee el texto de una o letra a letra


  //Bucle del juego
  while (GameMan.getWindow().isOpen()) {
    //Bucle de obtención de eventos
    inpSys.update();

    // Manejo de eventos de cerrar ventana
    sf::Event event;
    while (GameMan.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            GameMan.getWindow().close();
        }
    }

    phySys.update();

    //lo comento porque si no ahora mismo me borra todo por actualizarse todo el rato
    
    //renSys.update(); 
    

    //Resto del bucle principal del juego

    //Leemos el archivo de texto

    //Modificamos para que con una tecla pueda pasar a leer el texto entero

    if (!skip && std::getline(leer, linea))
    {
      std::cout << "NO SKIP" << std::endl;

      for (std::size_t i = 0; i < linea.size(); i++)
      {
        std::cout << "L BY L" << std::endl;

        texto.setString(texto.getString() + linea[i]);

        GameMan.getWindow().clear();
        GameMan.getWindow().draw(cuadro);
        GameMan.getWindow().draw(texto);
        GameMan.getWindow().display();

        //si pulsamos la tecla espacio salimos del bucle 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
          skip = true;
          continue;
        }

        sf::sleep(sf::milliseconds(100));
      }
      texto.setString(texto.getString() + "\n");
    } 
    else {
      std::cout << "CIERRO  " << std::endl;
      // Si hemos llegado al final del archivo, lo cerramos y reiniciamos
      leer.close();
      
    }
    
    
    //si se pulso espacio leemos todo el texto
  
    if(skip /*&& std::getline(leer, linea)*/){
      std::cout << "SKIP" << std::endl;
      std::string resto = "";
      
      while(std::getline(leer, linea)){

        resto += linea + "\n";

      }
      // //texto.setString(texto.getString() + resto);
      //texto.setString(resto);
      texto.setString(texto.getString() + resto + "\n");


      GameMan.getWindow().clear();
      GameMan.getWindow().draw(cuadro);
      GameMan.getWindow().draw(texto);
      GameMan.getWindow().display();

      // std::cout << "CIERRO 2 " << std::endl;
      // leer.close();

    }
    
  
    // Esperamos un poco antes de la siguiente iteración
    sf::sleep(sf::milliseconds(10));
//std::cout << "last get here" << player.physics->pos.x << std::endl;

  }

  return 0;
}
