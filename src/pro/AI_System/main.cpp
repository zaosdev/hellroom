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

  auto& player  = EM.createEntity();
  auto& enemy1  = EM.createEntity();


  // Creamos el player
  player.physics  = game::PhysicsComponent{ .pos{320, 240}, .vel{0,0}};
  player.render   = game::RenderComponent { .tex{}  , .Sprite{}, .window_Pos{320,240} };
  player.input    = game::InputComponent{};
  SPman.loadTexture(player.render->tex,"../resources/sprites.png");
  SPman.assignTexture(player.render->Sprite,player.render->tex);
  SPman.modifySpriteOrigin(player.render->Sprite,{75 / 2, 75 / 2});
  SPman.modifyTextureRect(player.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));
  

  //Create the enemy 1
  enemy1.physics = game::PhysicsComponent { .pos{0,0}, .vel{0,0}};
  enemy1.render  = game::RenderComponent  { .tex{}  , .Sprite{}, .window_Pos{0,0} };
  enemy1.AI      = game::AIComponent      { .targetCoord{640,480}}; 
  SPman.loadTexture(enemy1.render->tex,"../resources/sprites.png");
  SPman.assignTexture(enemy1.render->Sprite,enemy1.render->tex);
  SPman.modifySpriteOrigin(enemy1.render->Sprite,{75 / 2, 75 / 2});
  SPman.modifyTextureRect(enemy1.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

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