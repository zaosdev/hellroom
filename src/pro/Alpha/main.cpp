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
#include "utils/circularIterator.hpp"
#include "cmp/blackBoardComponent.hpp"


int main() {


  constexpr int screenWidth = 640;
  constexpr int screenHeight = 480;


  //Create Game manager
  FVeng::GameManager GameMan{screenWidth, screenHeight,"P0. Fundamentos de los Videojuegos. DCCIA"};

  //create Sprite manager
  SFMLeng::SpriteManager SPman{};

  //Create Game systems
  game::RenderSys     renSys{GameMan};
  game::PhysicsSys    phySys{GameMan};
  sf::RenderWindow&   window = GameMan.getWindow();
  game::InputManager  inpRec{window};
  game::InputSys      inpSys{GameMan, inpRec};
  game::AISys         AISys{GameMan};
  game::SoundSys      soundSys{GameMan, inpRec};
  game::AchievementSys achSys{GameMan};
  game::SavingSys saveSys{GameMan};




  GameMan.initGame();

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

      soundSys.update();
      // achSys.update();
      // saveSys.update();



    }

    std::cout << "updating render" << std::endl;
    // //Render game
    float percentTick = std::min(1.0, updateClock.getElapsedTime().asMilliseconds() / UPDATE_TICK_TIME); // ms / ms to get pt
    renSys.update(percentTick);

  }

  return 0;
}