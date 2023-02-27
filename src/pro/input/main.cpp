#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "classes/sys/renderSys.hpp"
#include "classes/sys/physicsSys.hpp"
#include "classes/sys/inputSys.hpp"
#include "classes/man/GameManager.hpp"
#include "classes/man/SpriteManager.hpp"
#include "classes/man/inputManager.cpp"


#define kVel 5

int main() {


  //Create Game manager
  FVeng::GameManager GameMan{640, 480,"Prototipo Input con multiples teclas"};

  //create Sprite manager
  SFMLeng::SpriteManager SPman{};

  //Create Game systems
  game::RenderSys     renSys{GameMan};
  game::PhysicsSys    phySys{GameMan};
  game::InputManager  inpRec{GameMan.getWindow()};
  game::InputSys      inpSys{GameMan, inpRec};
 


  GameMan.ent->render = new game::RenderComponent();
  GameMan.ent->physics = new game::PhysicsComponent();


  //Creamos una ventana
  SPman.loadTexture(GameMan.ent->render->tex,"../resources/sprites.png");

  //Y creo el spritesheet a partir de la imagen anterior
  SPman.assignTexture(GameMan.ent->render->Sprite,GameMan.ent->render->tex);
  //Le pongo el centroide donde corresponde
  SPman.modifySpriteOrigin(GameMan.ent->render->Sprite,{75 / 2, 75 / 2});
  //Cojo el sprite que me interesa por defecto del sheet
  SPman.modifyTextureRect(GameMan.ent->render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // Lo dispongo en el centro de la pantalla
  GameMan.ent->physics->pos = {320, 240};
  GameMan.ent->physics->vel = {0,0};

  GameMan.ent->render->Sprite.move(
    GameMan.ent->physics->pos.x,
    GameMan.ent->physics->pos.y
  );

//std::cout << "I get here" << GameMan.ent->physics->pos.x << std::endl;

  std::vector<sf::Event> events;  // Declarar un vector para almacenar los eventos
  //Bucle del juego
  while (GameMan.getWindow().isOpen()) {
    
    //Bucle de obtención de eventos
    inpRec.update();
    inpSys.update();
    phySys.update();
    renSys.update();

  }

  return 0;
}