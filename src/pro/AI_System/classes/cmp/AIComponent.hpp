#pragma once 
#include "../utils/math.hpp"

namespace game
{
    struct AIComponent
    {
        FVmath::vec2D targetCoord;        //get position for arriving
        //size_t  targetID;               //look at the player
    };
}