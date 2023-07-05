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


    void mainDepruebas(FVmath::Point2Di start, FVmath::Point2Di goal, std::vector<std::vector<int>>& map)
    {
         sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding A*");

        sf::RectangleShape tile(sf::Vector2f(10.f, 10.f));
        tile.setOutlineThickness(1.f);
        tile.setOutlineColor(sf::Color::Black);

    //     std::vector<std::vector<int>> transposedMap;

    //     for (size_t j = 0; j < map[0].size(); ++j) {
    //         std::vector<int> column;
    //         for (size_t i = 0; i < map.size(); ++i) {
    //             column.push_back(map[i][j]);
    //         }
    //         transposedMap.push_back(column);
    //     }
        int iteraciones = 0;
        std::vector<FVAI::PathNode> path = FVAI::findPathAStar(start, goal, map, iteraciones);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            for (int i = 0; i < map.size(); ++i)
            {
                for (int j = 0; j < map[i].size(); ++j)
                {
                    tile.setPosition(i * 10.f, j * 10.f);
                    if (i == start.x && j == start.y)
                    {
                        tile.setFillColor(sf::Color::Green);
                    }
                    else if (i == goal.x && j == goal.y)
                    {
                        tile.setFillColor(sf::Color::Red);
                    }
                    else if (map[i][j] == 1)
                    {
                        tile.setFillColor(sf::Color::Black);
                    }
                    else if (std::find_if(path.begin(), path.end(), [&](FVAI::PathNode* node) { return node->x == i && node->y == j; }) != path.end())
                    {
                        tile.setFillColor(sf::Color::Blue);
                    }
                    else
                    {
                        tile.setFillColor(sf::Color::White);
                    }
                    window.draw(tile);
                }
            }

            window.display();
        }

        for (auto& node : path)
        {
            delete node;
        }


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
                    case FVAI::SB::FOLLOWCIRCULARPATH:
                    {
                        addPos = FVAI::followCircularPath(ent.physics->pos, ent.AI->circularPath, ent.physics->mov_speed);
                        break;
                    }
                    case FVAI::SB::FOLLOWPATH:
                    {
                        addPos = FVAI::followPath(ent.physics->pos, ent.AI->linearPath, ent.physics->mov_speed);
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
                        auto bounds   = ent.render->Sprite.getGlobalBounds();
                        auto& pos      = ent.physics->pos;
                        FVmath::Point2Di startGrid = gMan_.worldPositionToGrid(pos.x + bounds.width / 2, pos.y + bounds.height / 2);
                        
                        //Calculate the position of the goal in the map representation
                        auto& playerPos      = gMan_.getPlayer().physics->pos;
                        auto playerBounds   = gMan_.getPlayer().render->Sprite.getGlobalBounds();
                        FVmath::Point2Di goalGrid = gMan_.worldPositionToGrid(playerPos.x + playerBounds.width / 2, playerPos.y + playerBounds.height / 2);
 
                        std::cout << "Player position:  " << playerPos << std::endl;

                        std::cout << "Goal Grid:  " << goalGrid << std::endl;

                        std::cout << "Start Grid: " << startGrid << std::endl;

                        //Calculate the points of the map representation to the real world
                        int iteraciones = 0;
                        ent.AI->linearPath = FVAI::findPathAStar(startGrid, goalGrid, gMan_.getMapGridRepresentation(), iteraciones);
                        std::cout << "Iteraciones: " << iteraciones << std::endl;
                        
                        //if(iteraciones > 400 && path != std::vector<FVAI::PathNode*> {}) mainDepruebas(startGrid, goalGrid, gMan_.getMapGridRepresentation());
                        
                        //ACTIVATE THE PATHFOLLOW


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