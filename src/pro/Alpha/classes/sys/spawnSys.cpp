#include "spawnSys.hpp"
#include <iostream>
namespace game
{
    SpawnSys::SpawnSys(FVeng::GameManager& Gman)
    : gMan_(Gman)
    {
    }

    void SpawnSys::SpawnEnemy(FVmath::Point2Di Pos)
    {
        auto enemyChoice = FVmath::calcualteRandom(2,1);

        switch (enemyChoice)
        {
        case 1:
            gMan_.createEnemyArrive(Pos,{320,240},0.1,4);
            break;
        case 2:
            gMan_.createEnemyPursue(Pos,{320,240},gMan_.getPlayer().id(),4);
            break;
        default:
            gMan_.createEnemyArrive(Pos,{320,240},0.1,4);
            break;
        }
    }
    void SpawnSys::SpawnPlayer(FVmath::Point2Di Pos)
    {
        gMan_.createPlayer(Pos);
    }

    FVmath::Point2Di SpawnSys::calculateSpawnPoint(tXMLeng::Spawner& spawnInfo)
    {

        //CALCULATE POINT ON THE X AXIS
        auto xAxisMax = spawnInfo.SpawnOrigin.x+spawnInfo.SpawnRange.x;

        auto xAxisPoint = FVmath::calcualteRandom(xAxisMax,spawnInfo.SpawnOrigin.x);

        //CALCULATE POINT ON THE Y AXIS
        auto yAxisMax = spawnInfo.SpawnOrigin.y+spawnInfo.SpawnRange.y;

        auto yAxisPoint = FVmath::calcualteRandom(yAxisMax,spawnInfo.SpawnOrigin.y);

        //RETURN RESULTING POINT
        return{xAxisPoint,yAxisPoint};

    }

    void SpawnSys::update()
    {
        //check if it's a valid entity
        auto valid = [](Entity const& e){ return e.alive() && e.Spawn;};

        //check if the spawner it's for enemies
        auto isEnemySpawner = [&](Entity const& e){return valid(e) && e.Spawn->SpawnInfo.type == tXMLeng::SpawnerType::EnemySpawner; };

        //check if it's ready for spawning
        auto ready2Spawn = [&](Entity const& e){return e.Spawn->TimerSpawn.getElapsedTime().asSeconds()>e.Spawn->minTime; };

        //check if it still has capacity to spawn more enemies
        auto hasCapacity = [&](Entity const& e){return e.Spawn->capacity< e.Spawn->maxCapacity; };

        for(auto& e : gMan_.getEntityManager())
        {
            auto f = isEnemySpawner(e);

            //std::cout << f << std::endl;

            if(isEnemySpawner(e) && ready2Spawn(e) && hasCapacity(e))
            {
               auto Pos = calculateSpawnPoint(e.Spawn->SpawnInfo);
               SpawnEnemy(Pos);
               e.Spawn->capacity++;
               e.Spawn->TimerSpawn.restart();
            }
        }
    }
}