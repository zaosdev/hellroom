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
        game::enemy_type enemy_spawned{game::enemy_type::NO_TYPE};
        object_type type {object_type::ENEMY};
        FVmath::Point2Di SpawnOrigin{};  //top-left-most point of the spawner 
        FVmath::Point2Di SpawnRange{};   //first value is its width, second value its height
    };

    struct DoorInfo
    {
        FVmath::Point2Di pos{};
        FVmath::Point2Di size{};
        std::string next_level_path{""};
    };

    struct room_trigger
    {
        FVmath::Point2Di pos{};
        FVmath::Point2Di size{};
    };

    struct room_blockage
    {
        FVmath::Point2Di pos{};
        FVmath::Point2Di size{};
    };

    struct Room
    {
        room_trigger trigger{};
        std::vector<room_blockage> blocks{};
        std::vector<Spawner> spawners{};
    };
}