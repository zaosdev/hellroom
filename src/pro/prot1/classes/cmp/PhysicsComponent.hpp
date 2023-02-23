#pragma once 
#include "../utils/math.hpp"

namespace game
{
    struct PhysicsComponent
    {
        FVmath::vec2D pos;
        FVmath::vec2D vel;
    };
}