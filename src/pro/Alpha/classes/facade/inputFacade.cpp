#include "inputFacade.hpp"
#include <iostream>
namespace KeyMapNamespace
{

    struct KeyMap {
        char Char;                      //'W'
        sf::Keyboard::Key keyCode;      //'SMFL Representation'
    };


    static const KeyMap keyMap[] = 
    {
        {'A', sf::Keyboard::A},
        {'B', sf::Keyboard::B},
        {'C', sf::Keyboard::C},
        {'D', sf::Keyboard::D},
        {'E', sf::Keyboard::E},
        {'F', sf::Keyboard::F},
        {'G', sf::Keyboard::G},
        {'H', sf::Keyboard::H},
        {'I', sf::Keyboard::I},
        {'J', sf::Keyboard::J},
        {'K', sf::Keyboard::K},
        {'L', sf::Keyboard::L},
        {'M', sf::Keyboard::M},
        {'N', sf::Keyboard::N},
        {'O', sf::Keyboard::O},
        {'P', sf::Keyboard::P},
        {'Q', sf::Keyboard::Q},
        {'R', sf::Keyboard::R},
        {'S', sf::Keyboard::S},
        {'T', sf::Keyboard::T},
        {'U', sf::Keyboard::U},
        {'V', sf::Keyboard::V},
        {'W', sf::Keyboard::W},
        {'X', sf::Keyboard::X},
        {'Y', sf::Keyboard::Y},
        {'Z', sf::Keyboard::Z},
        {'0', sf::Keyboard::Num0},
        {'1', sf::Keyboard::Num1},
        {'2', sf::Keyboard::Num2},
        {'3', sf::Keyboard::Num3},
        {'4', sf::Keyboard::Num4},
        {'5', sf::Keyboard::Num5},
        {'6', sf::Keyboard::Num6},
        {'7', sf::Keyboard::Num7},
        {'8', sf::Keyboard::Num8},
        {'9', sf::Keyboard::Num9},
        {' ', sf::Keyboard::Space},
        {'u', sf::Keyboard::Up},
        {'d', sf::Keyboard::Down},
        {'l', sf::Keyboard::Left},
        {'r', sf::Keyboard::Right}
    };
}


sf::Keyboard::Key getKeyCode(char key)
{
    
    

    //number of keys = size of map / size of every character
    static const int numKeys = sizeof(KeyMapNamespace::keyMap) / sizeof(KeyMapNamespace::keyMap[0]);

    //search the keycode (smfl code)
    for (int i = 0; i < numKeys; i++) { //run over all the map
        if (KeyMapNamespace::keyMap[i].Char == key) {    //check if the char given is the keychar
            return KeyMapNamespace::keyMap[i].keyCode;   //return the keycode
        }
    }
    std::cout << "Not mapped key: " << key << ", please add it on inputFacade.cpp" << std::endl;
    return sf::Keyboard::Unknown;
}