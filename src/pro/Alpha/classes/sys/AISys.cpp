#include "AISys.hpp"
#include "utils/AI.hpp"
#include <iostream>
#include "../define.h"



namespace game
{
    AISys::AISys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    bool AISys::perception(std::optional<game::AIComponent>& AI, FVeng::EntityManager<game::Entity>& EM,  blackBoardComponent& bb, double const dt)
    {
        //Check if accumulated time > cooldown
        AI->accumulatedTime += dt;
        if(AI->accumulatedTime <= AI->perceptionTime) return false;
            
        //Time passed: Unaccumulate time
        AI->accumulatedTime -= AI->perceptionTime;

        //Check blackboard
        if(bb.tActive)
        {
            AI->targetID    = bb.targetID;
            auto* targeted  = EM.getEntityByID(bb.targetID);
            if(targeted != nullptr)
            AI->targetCoord =  targeted->physics->pos;
        }
        return true;
    }

    void mainDepruebas()
    {
        
    }

    void AISys::update(blackBoardComponent bb, double const dt)
    {
        auto& EM = gMan_.getEntityManager();

        for(auto& ent : EM)
        {
            if(ent.AI && ent.physics)
            {
                ent.AI->timeAlive += dt;
                FVmath::Point2D addPos {};
                bool percep = perception(ent.AI, EM, bb, dt);
                switch(ent.AI->behaviour)
                {
                    case FVAI::SB::ARRIVE:
                    {
                        addPos = FVAI::arrive(ent.physics->pos, ent.AI->targetCoord, ent.physics->mov_speed, ent.AI->arrivalRadius, ent.AI->friction, true, ent.AI->time2arrive);
                        break;
                    }
                    case FVAI::SB::SEEK:
                    {
                        addPos = FVAI::seek(ent.physics->pos, ent.AI->targetCoord, ent.physics->mov_speed, ent.AI->arrivalRadius);
                        break;
                    }
                    case FVAI::SB::PURSUE:
                    {
                        auto* Target = EM.getEntityByID(ent.AI->targetID);
                        if(Target!=nullptr && Target->physics)
                        {
                            //Precalculate position
                            FVmath::Point2D proxTargetPos = Target->physics->pos + Target->physics->vel;
                            //Send to the AI
                            addPos = FVAI::pursue(ent.physics->pos, proxTargetPos, ent.physics->mov_speed, ent.AI->arrivalRadius);
                        }
                        break;
                    }
                    case FVAI::SB::FLEE:
                    {
                        addPos = FVAI::flee(ent.physics->pos, ent.AI->targetCoord, ent.physics->mov_speed);
                        break;
                    }
                    case FVAI::SB::CROSSCREEN:
                    {
                        addPos = FVAI::cross(ent.AI->priotiryCross, ent.physics->mov_speed);
                        break;
                    }
                    case FVAI::SB::FOLLOWPATH:
                    {
                        addPos = FVAI::followPath(ent.physics->pos, ent.AI->path, ent.physics->mov_speed);
                        break;
                    }
                    case FVAI::SB::STAY:
                    {
                        addPos = FVAI::stay();
                        break;
                    }
                    case FVAI::SB::SHOOTATTACK:
                    {
                        addPos = FVAI::stay();
                        if(percep)
                        {
                            //Generate a bullet from the enemy to the player position
                            gMan_.createEnemyBullet(ent.physics->pos, FVAI::SB::SEEK, gMan_.getPlayer().physics->pos);
                        }                    
                        break;
                    }
                    case FVAI::SB::PATHFINDING:
                    {
                        //creates a path to the point and then uses followpath to run over the points
                        //Calculate the position of the enemy in the map representation
                        auto& pos   = ent.physics->pos;
                        FVmath::Point2Di startGrid = gMan_.worldPositionToGrid(pos.x, pos.y);
                        
                        //Calculate the position of the goal in the map representation
                        auto& playerPos  = gMan_.getPlayer().physics->pos;
                        FVmath::Point2Di goalGrid = gMan_.worldPositionToGrid(playerPos.x, playerPos.y);
 
                        std::cout << "Player position:  " << playerPos << std::endl;

                        std::cout << "Goal Grid:  " << goalGrid << std::endl;

                        std::cout << "Start Grid: " << startGrid << std::endl;

                        //Calculate the points of the map representation to the real world
                        auto path = FVAI::findPathAStar({startGrid.y, startGrid.x}, {goalGrid.y, goalGrid.x}, gMan_.getMapGridRepresentation());
                        std::cout << "Salgo del pathdfingind" << std::endl;

                        mainDepruebas();
                        break;
                    }
                    default:break;
                }
                if((ent.AI->maxTimeAlive != -1) && (ent.AI->timeAlive > ent.AI->maxTimeAlive)) ent.mark4destruction();
                ent.physics->vel = addPos;

                // if(ent.weapon)
                // {
                //     ent.weapon->direction = directionType::este; // por probar
                //     ent.weapon->on;
                // }
            }

        }  
    }
}