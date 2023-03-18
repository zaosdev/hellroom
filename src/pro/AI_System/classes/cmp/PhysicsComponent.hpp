#pragma once 
#include "../utils/math.hpp"

namespace game
{
    struct PhysicsComponent
    {
        FVmath::Point2D pos;
        FVmath::Point2D vel;
    };
}