#include "spawnSys.hpp"
#include <iostream>
namespace game
{
    SpawnSys::SpawnSys(FVeng::GameManager& Gman)
    : gMan_(Gman)
    {
    }



    void SpawnSys::SpawnEnemy(FVmath::Point2Di Pos,auto enemyshit, size_t& enemyID)
    {

        // gMan_.SpawnDummy(Pos);
        // auto enemyChoice = FVmath::calculateRandom(3,1);
        
        // switch (enemyChoice)
        // {
        //     case game::enemy_type::ARRIVE :
        //      enemyID = gMan_.createEnemyArrive(Pos,{320,240},0.1,4);
        //     break;

        //     case game::enemy_type::PURSUE :
        //      enemyID = gMan_.createEnemyPursue(Pos,{320,240},gMan_.getPlayer().id(),3);
        //     break;

        //     case game::enemy_type::SHOOT : 
        //      enemyID = gMan_.createEnemyShoot(Pos,{320,240},gMan_.getPlayer().id(),4);
        //     break;

        //     case game::enemy_type::NO_TYPE: 
        //     default:
        //      enemyID = gMan_.createEnemyArrive(Pos,{320,240},0.1,4);
        //     break;
        // }

        static bool spawn = true;
        if(spawn) 
        {
            spawn = false;
            gMan_.createEnemyPursue(Pos,{320,240},gMan_.getPlayer().id(),3);
        }
    }
    void SpawnSys::SpawnPlayer()
    {
        setPlayerSpawner();
        auto& EM = gMan_.getEntityManager();

        auto& e = *EM.getEntityByID(player_spawner_id_);

        auto Pos = calculateSpawnPoint(e.Spawn->SpawnInfo);
        
        auto& player = gMan_.getPlayer();

        player.physics->pos = FVmath::Point2D{float(Pos.x),float(Pos.y)};

        e.Spawn->capacity++;
    }

    void SpawnSys::setPlayerSpawner()
    {
        auto& EM = gMan_.getEntityManager();
        for(auto& e : EM)
            if(e.alive() && e.Spawn->SpawnInfo.type & tXMLeng::object_type::PLAYER)  player_spawner_id_= e.id();
        
    }

    FVmath::Point2Di SpawnSys::calculateSpawnPoint(tXMLeng::Spawner& spawnInfo)
    {

        //CALCULATE POINT ON THE X AXIS
        auto xAxisMax = spawnInfo.SpawnOrigin.x+spawnInfo.SpawnRange.x;

        auto xAxisPoint = FVmath::calculateRandom(xAxisMax,spawnInfo.SpawnOrigin.x);

        //CALCULATE POINT ON THE Y AXIS
        auto yAxisMax = spawnInfo.SpawnOrigin.y+spawnInfo.SpawnRange.y;

        auto yAxisPoint = FVmath::calculateRandom(yAxisMax,spawnInfo.SpawnOrigin.y);

        //RETURN RESULTING POINT
        return{xAxisPoint,yAxisPoint};

    }

    void SpawnSys::setEnemyRoom(size_t roomID,size_t enemyID)
    {
       auto& EM = gMan_.getEntityManager();

       auto& room = *EM.getEntityByID(roomID);

       room.room->room_enemies.emplace_back(enemyID);
    }


    void SpawnSys::update()
    {
        //check if it's a valid entity
        auto valid = [](Entity const& e){ return e.alive() && e.Spawn && e.hasTag(game::Entity::TAG::SPAWNER);};

        //check if the spawner it's for enemies
        auto isEnemySpawner = [&](Entity const& e){return valid(e) && e.Spawn->SpawnInfo.type == tXMLeng::object_type::ENEMY; };

        //check if it's ready for spawning
        auto ready2Spawn = [&](Entity const& e){return e.Spawn->TimerSpawn.getElapsedTime().asSeconds()>e.Spawn->minTime; };

        //check if it still has capacity to spawn more enemies
        auto hasCapacity = [&](Entity const& e){return e.Spawn->capacity < e.Spawn->maxCapacity; };

        for(auto& e : gMan_.getEntityManager())
        {            
            if(isEnemySpawner(e) && ready2Spawn(e) && hasCapacity(e))
            {        
                auto Pos = calculateSpawnPoint(e.Spawn->SpawnInfo);
                size_t tempID{};
                SpawnEnemy(Pos,e.Spawn->SpawnInfo.enemy_spawned,tempID);
                if(e.Spawn->ownerID!=0)  setEnemyRoom(e.Spawn->ownerID,tempID);
                e.Spawn->capacity++;
                e.Spawn->TimerSpawn.restart();
                if(e.Spawn->capacity == e.Spawn->maxCapacity)
                {
                    e.Spawn->fullCapacity=true;
                }
            }
        }
    }
}