#pragma once 
#include "../utils/math.hpp"

namespace game
{
    struct PhysicsComponent
    {
        FVmath::Point2D pos;
        FVmath::Point2D vel;       //value so add to pos
        double          mov_speed; //fixed value to use for calculate vel
    };
}