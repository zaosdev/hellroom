#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGTH 480

namespace MaquinaEstados{
    class State{

        public:
            virtual void Pause( ) {}
            virtual void Resume( ) {}
    };

}