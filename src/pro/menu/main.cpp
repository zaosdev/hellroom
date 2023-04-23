#include "SFML/Graphics.hpp"
#include <iostream>
#include "classes/man/Menu.hpp"

int main(){
  sf::RenderWindow window(sf::VideoMode(600,600), "SFML WORK!");

  Menu menu(window.getSize().x, window.getSize().y);

  while(window.isOpen()){
    sf::Event event;

    while(window.pollEvent(event)){
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      }
    }

    window.clear();
    menu.draw(window);
    window.display();
  }
}