#pragma once 
#include "../utils/math.hpp"

namespace game
{
    struct PhysicsComponent
    {
        FVmath::Point2D pos;
        FVmath::Point2D prevPos;
        FVmath::Point2D vel;       //value so add to pos (pixels per second)
        float          mov_speed; //fixed value to use for calculate vel
    };
}