#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "classes/man/stateManager.hpp"
#include "include/config.h"
#include "define.h"

int main() {
  FVEng::StateMachine StateMachine{screenWidth, screenHeight, "Hellroom"};
  StateMachine.ChangeToMainMenuState(true);
  while(StateMachine.getWindow().isOpen())
  {
      StateMachine.ProcessStateChanges();
      StateMachine.GetActivateState()->executeState();
  }

  return 0;
}