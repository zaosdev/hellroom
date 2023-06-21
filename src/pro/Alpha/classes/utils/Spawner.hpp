#pragma once

#include "../utils/math.hpp"
#include "../cmp/AIComponent.hpp"


namespace tXMLeng
{
    enum object_type
    {
        PLAYER  = 1 << 0,
        ENEMY   = 1 << 1,
        COFFER  = 1 << 2,
        TRAP    = 1 << 3,
        NONE    = 1 << 4,

    };

    struct Spawner
    {
        game::enemy_type enemy_spawned{game::enemy_type::NONE};
        object_type type {object_type::ENEMY};
        FVmath::Point2Di SpawnOrigin{};  //top-left-most point of the spawner 
        FVmath::Point2Di SpawnRange{};   //first value is its width, second value its height
    };
}