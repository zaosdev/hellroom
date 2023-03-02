#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGTH 480

namespace MaquinaEstados{
    class State{

        public:
            virtual void Init( ) = 0;

            virtual void HandleInput( ) = 0;
            virtual void Update( ) = 0;
            virtual void Draw( float dt) = 0;

            virtual void Pause( ) {}
            virtual void Resume( ) {}
    };

}