#pragma once

#include "../man/GameManager.hpp"
#include "../utils/random.hpp"
#include "../utils/math.hpp"


namespace game
{
    struct SpawnSys
    {
        SpawnSys(FVeng::GameManager& Gman);
        ~SpawnSys() = default;

        SpawnSys (const SpawnSys&) = delete;
        SpawnSys (SpawnSys&&) = delete;
        SpawnSys& operator=(const SpawnSys&)= delete;
        SpawnSys& operator=(SpawnSys&&)= delete;

        void iniSpawnSys();

        void SpawnEnemy(FVmath::Point2Di Pos);
        void SpawnPlayer(FVmath::Point2Di Pos);
        FVmath::Point2Di calculateSpawnPoint(tXMLeng::Spawner& spawnInfo);

        void update();


        private:
            FVeng::GameManager& gMan_;
    };
}