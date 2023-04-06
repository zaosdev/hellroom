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
            gMan_.createEnemyArrive(Pos,{320,240},0.1,1);
            break;
        case 2:
            gMan_.createEnemyPursue(Pos,{320,240},gMan_.getPlayer().id(),1);
            break;
        default:
            gMan_.createEnemyArrive(Pos,{320,240},0.1,1);
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
        for(auto& e : gMan_.getEntityManager())
        {
            if(e.Spawn && e.Spawn->SpawnInfo.type== tXMLeng::SpawnerType::EnemySpawner)
            {
                std::cout << "reo ENEMigo" << std::endl;
               auto Pos = calculateSpawnPoint(e.Spawn->SpawnInfo);
               SpawnEnemy(Pos);
            }
        }
    }
}