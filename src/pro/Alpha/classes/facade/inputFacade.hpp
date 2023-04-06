#pragma once 
#include <SFML/Graphics.hpp>

using Key                                   = sf::Keyboard::Key;
using Event_t                               = sf::Event;
const sf::Event::EventType KeyPressed       = sf::Event::KeyPressed;
const sf::Event::EventType KeyReleased      = sf::Event::KeyReleased;
const sf::Event::EventType Closed           = sf::Event::Closed;

sf::Keyboard::Key getKeyCode(char key);
