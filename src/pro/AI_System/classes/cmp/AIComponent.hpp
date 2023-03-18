#pragma once 
#include "../utils/math.hpp"
#include "../utils/AI.hpp"
#include "../utils/types.hpp"

namespace game
{
    struct Entity; // Forward declaration de la estructura Entity
    struct AIComponent
    {
        FVmath::Point2D  targetCoord;        //get position for arriving
        FVAI::SB         behaviour;          //behaviour of entity
        EntityIDType     targetID;           //look at the player
    };
}