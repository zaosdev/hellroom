#pragma once

#include "../utils/math.hpp"

namespace tXMLeng
{
    enum class SpawnerType
    {
        PlayerSpawner,
        EnemySpawner,
    };

    struct Spawner
    {
        SpawnerType type = SpawnerType::EnemySpawner;
        FVmath::Point2Di SpawnOrigin{};  //top-left-most point of the spawner 
        FVmath::Point2Di SpawnRange{};   //first value is its width, second value its height
    };
}