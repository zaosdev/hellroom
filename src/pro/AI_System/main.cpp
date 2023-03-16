#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "classes/sys/renderSys.hpp"
#include "classes/sys/physicsSys.hpp"
#include "classes/sys/inputSys.hpp"
#include "classes/man/GameManager.hpp"
#include "classes/man/SpriteManager.hpp"
#include "classes/man/inputManager.hpp"


#define kVel 5

int main() {


  //Create Game manager
  FVeng::GameManager GameMan{640, 480,"P0. Fundamentos de los Videojuegos. DCCIA"};

  //create Sprite manager
  SFMLeng::SpriteManager SPman{};

  //Create Game systems
  game::RenderSys     renSys{GameMan};
  game::PhysicsSys    phySys{GameMan};
  game::InputManager  inpRec{GameMan.getWindow()};
  game::InputSys      inpSys{GameMan, inpRec};


  auto& EM = GameMan.getEntityManager();

  auto& player = EM.createEntity();


  // Lo dispongo en el centro de la pantalla
  player.physics = game::PhysicsComponent{ .pos{320, 240}, .vel{0,0}};

  player.render = game::RenderComponent { .tex{}  , .Sprite{}, .window_Pos{320,240} };

  player.input = game::InputComponent{};

  //Creamos una ventana
  SPman.loadTexture(player.render->tex,"../resources/sprites.png");
  //Y creo el spritesheet a partir de la imagen anterior
  SPman.assignTexture(player.render->Sprite,player.render->tex);
  //Le pongo el centroide donde corresponde
  SPman.modifySpriteOrigin(player.render->Sprite,{75 / 2, 75 / 2});
  //Cojo el sprite que me interesa por defecto del sheet
  SPman.modifyTextureRect(player.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

std::cout << "I get here" << player.physics->pos.x << std::endl;
    player.render->Sprite.move(
      player.physics->pos.x,
      player.physics->pos.y
  );
  //Bucle del juego
  while (GameMan.getWindow().isOpen()) 
  {
    std::cout << "HOLA??" << player.physics->pos.x << std::endl;
    //Bucle de obtención de eventos
    inpRec.update();std::cout << "HOLA despues de inprec??" << player.physics->pos.x << std::endl;
    inpSys.update();
    std::cout << "I get here" << player.physics->pos.x << std::endl;

    //Update physics
    phySys.update();

    //Render game
    renSys.update();
  }

  return 0;
}