#include "inputSys.hpp"

#define dash_multiplier 3
#define movement_speed  5
namespace game
{
    InputSys::InputSys(FVeng::GameManager& gameMan, InputManager& inpMan)
    : gMan_(gameMan), inpRec_(inpMan)
    {
    }

    void InputSys::update()
    {
        gMan_.ent->physics->vel = {0,0};

        //Movement
        if(inpRec_.isKeyPressed(sf::Keyboard::Key::W))      gMan_.ent->physics->vel += {0,-movement_speed}; 
        if(inpRec_.isKeyPressed(sf::Keyboard::Key::A))      gMan_.ent->physics->vel += {-movement_speed,0}; 
        if(inpRec_.isKeyPressed(sf::Keyboard::Key::S))      gMan_.ent->physics->vel += {0,movement_speed}; 
        if(inpRec_.isKeyPressed(sf::Keyboard::Key::D))      gMan_.ent->physics->vel += {movement_speed,0}; 

        //Dash
        if(inpRec_.isKeyPressed(sf::Keyboard::Key::Space))
        {
            gMan_.ent->physics->vel.x *= dash_multiplier;
            gMan_.ent->physics->vel.y *= dash_multiplier; 
        }  

    }

}

