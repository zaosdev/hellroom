#pragma once 
#include "../utils/math.hpp"
#include "../utils/AI.hpp"

namespace game
{
    struct AIComponent
    {
        FVmath::vec2D targetCoord;        //get position for arriving
        FVAI::SB        behaviour;        //behaviour of entity
        //size_t  targetID;               //look at the player
    };
}