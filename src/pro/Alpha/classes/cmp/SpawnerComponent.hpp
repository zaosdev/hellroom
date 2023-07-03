#pragma once 

#include "../utils/map_types.hpp"

namespace game
{


    struct SpawnerComponent
    {
        tXMLeng::Spawner SpawnInfo{};
        sf::Clock TimerSpawn{};
        float minTime{1};
        size_t capacity{0};
        size_t maxCapacity{1};
        bool fullCapacity{false};
        bool enabled{false};

        size_t ownerID{};

    };
}