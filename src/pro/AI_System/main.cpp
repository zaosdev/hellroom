#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "include/config.h"
#include "classes/sys/renderSys.hpp"
#include "classes/sys/physicsSys.hpp"
#include "classes/sys/inputSys.hpp"
#include "classes/man/GameManager.hpp"
#include "classes/man/SpriteManager.hpp"
#include "classes/man/inputManager.hpp"
#include "classes/sys/AISys.hpp"
#include "utils/circularIterator.hpp"
#include "cmp/blackBoardComponent.hpp"

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
  game::AISys         AISys {GameMan};

  auto& EM = GameMan.getEntityManager();

  auto& player  = EM.createEntity();
  auto& enemy1  = EM.createEntity(); //ARRIVE
  auto& enemy2  = EM.createEntity(); //PURSUE 
  auto& enemy3  = EM.createEntity(); //SEEK
  auto& enemy4  = EM.createEntity(); //FLEE
  auto& enemy5  = EM.createEntity(); //CROSSCREEN
  auto& enemy6  = EM.createEntity(); //FOLLOWPATH

  auto tex = SPman.loadTexture("../resources/sprites.png");

  // Lo dispongo en el centro de la pantalla
  player.physics = game::PhysicsComponent{ .pos{320, 240}, .vel{0,0}, .mov_speed = 640/3}; //640 --> ancho de pantalla / 3 --> 3 segundos para cruzar la pantalla en ancho
  player.render = game::RenderComponent { .texIndex=tex  , .Sprite{}, .window_Pos{320,240} };
  player.input = game::InputComponent{};

  SPman.assignTexture(player.render->Sprite,player.render->texIndex);
  SPman.modifySpriteOrigin(player.render->Sprite,{75 / 2, 75 / 2});
  SPman.modifyTextureRect(player.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));
 

  //Create the enemy 1 : ARRIVE BEHAVIOUR
  // enemy1.physics = game::PhysicsComponent { .pos{0,0}, .vel{0,0}, .mov_speed = 4};
  // enemy1.render  = game::RenderComponent  { .texIndex=tex  , .Sprite{}, .window_Pos{0,0} };
  // enemy1.AI      = game::AIComponent      { .targetCoord{640,480}, .behaviour = FVAI::SB::ARRIVE, .friction = 3, .perceptionTime = 3}; 
  // SPman.assignTexture(enemy1.render->Sprite,enemy1.render->texIndex);
  // SPman.modifySpriteOrigin(enemy1.render->Sprite,{75 / 2, 75 / 2});
  // SPman.modifyTextureRect(enemy1.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // //Create the enemy 2 : PURSUE BEHAVIOUR
  // enemy2.physics = game::PhysicsComponent { .pos{0,0}, .vel{0,0}, .mov_speed = 4};
  // enemy2.render  = game::RenderComponent  { .texIndex=tex  , .Sprite{}, .window_Pos{0,0} };
  // enemy2.AI      = game::AIComponent      { .targetCoord{640,480}, .behaviour = FVAI::SB::PURSUE, .targetID = player.id(), .perceptionTime = 1}; 
  // SPman.assignTexture(enemy2.render->Sprite,enemy2.render->texIndex);
  // SPman.modifySpriteOrigin(enemy2.render->Sprite,{75 / 2, 75 / 2});
  // SPman.modifyTextureRect(enemy2.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // //Create the enemy 3 : SEEK BEHAVIOUR
  // enemy3.physics = game::PhysicsComponent { .pos{0,0}, .vel{0,0}, .mov_speed = 4};
  // enemy3.render  = game::RenderComponent  { .texIndex=tex  , .Sprite{}, .window_Pos{0,0} };
  // enemy3.AI      = game::AIComponent      { .targetCoord{640,480}, .behaviour = FVAI::SB::SEEK, .perceptionTime = 2}; 
  // SPman.assignTexture(enemy3.render->Sprite,enemy3.render->texIndex);
  // SPman.modifySpriteOrigin(enemy3.render->Sprite,{75 / 2, 75 / 2});
  // SPman.modifyTextureRect(enemy3.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // //Create the enemy 4 : FLEE BEHAVIOUR
  // enemy4.physics = game::PhysicsComponent { .pos{640,480}, .vel{0,0}, .mov_speed = 1};
  // enemy4.render  = game::RenderComponent  { .texIndex=tex  , .Sprite{}, .window_Pos{640,480} };
  // enemy4.AI      = game::AIComponent      { .targetCoord{641,481}, .behaviour = FVAI::SB::FLEE, .targetID = player.id()}; 
  // SPman.assignTexture(enemy4.render->Sprite,enemy4.render->texIndex);
  // SPman.modifySpriteOrigin(enemy4.render->Sprite,{75 / 2, 75 / 2});
  // SPman.modifyTextureRect(enemy4.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // //Create the enemy 5 : CROSSCREEN BEHAVIOUR
  // enemy5.physics = game::PhysicsComponent { .pos{0,0}, .vel{0,0}, .mov_speed = 1};
  // enemy5.render  = game::RenderComponent  { .texIndex=tex  , .Sprite{}, .window_Pos{0,0} };
  // enemy5.AI      = game::AIComponent      { .targetCoord{641,481}, .behaviour = FVAI::SB::CROSSCREEN, .targetID = player.id(), .priotiryCross=FVAI::PriotiryCross::FIRSTY}; 
  // SPman.assignTexture(enemy5.render->Sprite,enemy5.render->texIndex);
  // SPman.modifySpriteOrigin(enemy5.render->Sprite,{75 / 2, 75 / 2});
  // SPman.modifyTextureRect(enemy5.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // //Create the enemy 6 : FOLLOWPATH BEHAVIOUR
  // std::vector<FVAI::circularIterator::PointType> path {{50,200}, {250,200}, {250,0}, {50,0}};
  // FVAI::circularIterator iterator;
  // iterator.setPath(path);

  // enemy6.physics = game::PhysicsComponent { .pos{0,0}, .vel{0,0}, .mov_speed = 1};
  // enemy6.render  = game::RenderComponent  { .texIndex=tex  , .Sprite{}, .window_Pos{0,0} };
  // enemy6.AI      = game::AIComponent      { .targetCoord{641,481}, .behaviour = FVAI::SB::FOLLOWPATH, .targetID = player.id(), .path = iterator}; 
  // SPman.assignTexture(enemy6.render->Sprite,enemy6.render->texIndex);
  // SPman.modifySpriteOrigin(enemy6.render->Sprite,{75 / 2, 75 / 2});
  // SPman.modifyTextureRect(enemy6.render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  //Create blackboard for updating the targetIDs
  game::blackBoardComponent bb {.targetID = player.id()};
  //bb.tActive = false;

  //Game clock
  sf::Clock clock;
  sf::Clock updateClock;
  static double UPDATE_TICK_TIME = 1000 / 15; //15fps for the systems, 60 fps por the render

  //Bucle del juego
  while (GameMan.getWindow().isOpen()) 
  {
    // //Update entities in manager
    GameMan.getEntityManager().update();

    if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
    {
        //restart the clock and get dt
        double dt = updateClock.restart().asSeconds();
    
        // //Update controls
        inpRec.update();
        inpSys.update();

        // //Update AI 
        AISys.update(bb, dt);

        // //Update physics
        phySys.update(dt);
    }
    
    // //Render game
    float percentTick = std::min(1.0, updateClock.getElapsedTime().asSeconds() / UPDATE_TICK_TIME);
    renSys.update(percentTick);
  }

  return 0;
}