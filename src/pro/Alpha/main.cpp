#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "classes/sys/renderSys.hpp"
#include "classes/sys/physicsSys.hpp"
#include "classes/sys/inputSys.hpp"
#include "classes/sys/soundSys.hpp"
#include "classes/sys/achievementSys.hpp"
#include "classes/sys/savingSys.hpp"
#include "classes/man/GameManager.hpp"
#include "classes/man/inputManager.hpp"
#include "classes/sys/AISys.hpp"
#include "classes/sys/spawnSys.hpp"
#include "classes/sys/healthSys.hpp"
#include "classes/sys/HUDSys.hpp"
#include "classes/sys/collisionSys.hpp"

#include "utils/circularIterator.hpp"
#include "cmp/blackBoardComponent.hpp"


int main() {



  constexpr int screenWidth = 640;
  constexpr int screenHeight = 480;


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

      //soundSys.update();

      healthSys.update(dt);
      //achSys.update();
      //saveSys.update();
    }

    //std::cout << "updating render" << std::endl;
    // //Render game
    float percentTick = std::min(1.0, updateClock.getElapsedTime().asMilliseconds() / UPDATE_TICK_TIME); // ms / ms to get pt
    renSys.update(percentTick);
  }

  return 0;
}