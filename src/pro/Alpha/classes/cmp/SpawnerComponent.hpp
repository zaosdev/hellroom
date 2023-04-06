#pragma once 
#include "../utils/Spawner.hpp"

namespace game
{
    struct SpawnerComponent
    {
        tXMLeng::Spawner SpawnInfo{};
        sf::Clock TimerSpawn{};
        float minTime{5};
        size_t capacity{0};
        size_t maxCapacity{5};

    };
}