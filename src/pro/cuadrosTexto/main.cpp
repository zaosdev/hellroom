#include <SFML/Graphics.hpp>
#include <iostream>
//librerias necesarias para leer texto 
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
  FVeng::GameManager GameMan{640, 480,"P2. Cuadros de Texto"};

  //create Sprite manager
  SFMLeng::SpriteManager SPman{};

  //Create Game systems
  game::RenderSys   renSys{GameMan};
  game::PhysicsSys  phySys{GameMan};
  game::InputSys    inpSys{GameMan};


  auto& EM = GameMan.getEntityManager();

  // auto& player = EM.createEntity();


  // // Lo dispongo en el centro de la pantalla
  // player.physics = game::PhysicsComponent{ .pos{320, 240}, .vel{0,0}};

  // player.render = game::RenderComponent { .tex{}  , .Sprite{}, .window_Pos{320,240} };

  // player.input = game::InputComponent{};

//   //Creamos una ventana
//   SPman.loadTexture(player.render->tex,"../resources/sprites.png");
//   //Y creo el spritesheet a partir de la imagen anterior
//   SPman.assignTexture(player.render->Sprite,player.render->tex);
//   //Le pongo el centroide donde corresponde
//   SPman.modifySpriteOrigin(player.render->Sprite,{75 / 2, 75 / 2});
//   //Cojo el sprite que me interesa por defecto del sheet
//   SPman.modifyTextureRect(player.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));
//   //muevo el sprite a la posicion determinada por el componente de fisica
// std::cout << "I get here" << player.physics->pos.x << std::endl;

//   player.render->Sprite.move(
//       player.physics->pos.x,
//       player.physics->pos.y
//   );

  //Aqui empiezo el codigo de cuadros de texto
  //Leemos el archivo de texto
  std::ifstream leer("resources/texto.txt");
  std::string linea;

  std::cout << "ARCHIVO LISTO" << std::endl;

  //para que salga el texto en pantalla necesito un obj texto

  sf::Font fuente;
  fuente.loadFromFile("resources/Minecraft.ttf"); //fuente con la que se vera el texto
  sf::Text texto("", fuente, 16);
  texto.setFillColor(sf::Color::Yellow);
  texto.setPosition(10,10);
  
  std::cout << "Todo bien hasta aqui" << std::endl;

  while(std::getline(leer, linea)){

    std::cout << "Leo linea a linea" << std::endl;

    for(int i = 0; i< linea.size(); i++){

      texto.setString(texto.getString() + linea[i]);

      GameMan.getWindow().clear();
      GameMan.getWindow().draw(texto);
      GameMan.getWindow().display();

      sf::sleep(sf::milliseconds(100));

    }
    texto.setString(texto.getString() + "\n");
  }

  //Bucle del juego
  while (GameMan.getWindow().isOpen()) {
    //Bucle de obtención de eventos
    inpSys.update();

    phySys.update();

    renSys.update();
//std::cout << "last get here" << player.physics->pos.x << std::endl;

  }

  return 0;
}