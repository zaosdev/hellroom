#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "classes/man/stateManager.hpp"
#include "classes/states/mainMenuState.cpp"
#include "include/config.h"

int main() {

  constexpr int screenWidth  = 640;
  constexpr int screenHeight = 480;

<<<<<<< HEAD

  //Create Game manager
  FVeng::GameManager GameMan{screenWidth, screenHeight, "Hellroom"};

  //create Sprite manager
  SFMLeng::SpriteManager SPman{};

  //Create Game systems
  game::PhysicsSys        phySys{GameMan};
  sf::RenderWindow&       window = GameMan.getWindow();
  game::InputManager      inpRec{window};
  game::InputSys          inpSys{GameMan, inpRec};
  game::AISys             AISys{GameMan};
  game::HealthSys         healthSys{GameMan};
  game::SpawnSys          spwnSys{GameMan};
  game::SoundSys          soundSys{GameMan, inpRec};
  game::AchievementSys    achSys{GameMan};
  game::SavingSys         saveSys{GameMan};
  game::CollisionSys      collisionSys{GameMan/*, SPman*/};
  //create the player and update(needed fot the hud)
  GameMan.initGame();
  GameMan.getEntityManager().update();

  game::HUDSys            HudSys{GameMan};


  game::RenderSys         renSys{GameMan, HudSys};
  //renSys.iniRenderSys(HudSys);
  //renSys.addHUD(HudSys);

  //Game clock
  sf::Clock clock;
  sf::Clock updateClock;
  constexpr double UPDATE_TICK_TIME = 1000 / 15; //15fps for the systems, 60 fps por the renders

  soundSys.loadSounds();
  

  //Bucle del juego
  while (GameMan.getWindow().isOpen()) {
    //Bucle de obtención de eventos

   

    GameMan.getEntityManager().update();
    if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
    {
      double dt = updateClock.restart().asSeconds();

      
      inpRec.update();
      inpSys.update();

      
      AISys.update(GameMan.getBB(), dt);

      phySys.update(dt);

      collisionSys.update();

      //IN THE FUTURE THIS MUST BE AFTER COLLSYS UPDATE
      spwnSys.update();

      soundSys.update();

      healthSys.update(dt);
      //achSys.update();
      //saveSys.update();
    }

    //std::cout << "updating render" << std::endl;
    // //Render game
    float percentTick = std::min(1.0, updateClock.getElapsedTime().asMilliseconds() / UPDATE_TICK_TIME); // ms / ms to get pt
    renSys.update(percentTick);
=======
  FVEng::StateMachine StateMachine{screenWidth, screenHeight, "Hellroom"};
  StateMachine.AddState(std::make_unique<FVEng::mainMenuState>(StateMachine.getWindow(), StateMachine), true);
  while(StateMachine.getWindow().isOpen())
  {
      StateMachine.ProcessStateChanges();
      StateMachine.GetActivateState()->executeState();
>>>>>>> developer
  }

  return 0;
}