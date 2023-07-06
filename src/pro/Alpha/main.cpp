#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "classes/man/stateManager.hpp"
#include "classes/states/mainMenuState.hpp"
#include "include/config.h"
#include "define.h"

int main() {
  FVEng::StateMachine StateMachine{screenWidth, screenHeight, "Hellroom"};
  StateMachine.AddState(std::make_unique<FVEng::mainMenuState>(StateMachine.getWindow(), StateMachine), true);
  while(StateMachine.getWindow().isOpen())
  {
      StateMachine.ProcessStateChanges();
      StateMachine.GetActivateState()->executeState();
  }

  return 0;
}