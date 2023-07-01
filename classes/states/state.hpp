
#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGTH 480

namespace FVEng{
    class State{

        public:
            virtual void Init( ) = 0;

            virtual void executeState( ) = 0;

            virtual void Pause( ) {}
            virtual void Resume( ) {}

            virtual ~State() = default; // Destructor virtual puro
    };

}