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

        std::vector<FVmath::Point2Di> path = FVAI::findPathAStar(start, goal, map);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            for (int i = 0; i < static_cast<int>(map.size()); ++i)
            {
                for (int j = 0; j < static_cast<int>(map[i].size()); ++j)
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
                    else if (std::find_if(path.begin(), path.end(), [&](FVmath::Point2Di node) { return node.x == i && node.y == j; }) != path.end())
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

        // for (auto& node : path)
        // {
        //     delete node;
        // }


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

                //If the distance to the player is to high, dont even bother to activate this entity AI
                if(FVmath::calculateDistance(ent.physics->pos, gMan_.getPlayer().physics->pos) > MAX_DISTANCE) {continue;}



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
                        //set the size to a lower so it can move better into stretch places
                        ent.physics->size = {pathfindingSize, pathfindingSize};
                        std::cout << "bh = followpath" << std::endl;
                        bool isOver = false;
                        addPos = FVAI::followPath(ent.physics->pos, ent.AI->linearPath, ent.physics->mov_speed, isOver);
                        if(isOver) 
                        {
                            //ent.AI->behaviour = FVAI::SB::PATHFINDING;
                            ent.AI->behaviour = ent.AI->originalBehaviour; //once the path is ended, return to the previous behaviour
                            //return to normal size
                            ent.physics->size = {defSize, defSize};
                            //add little random values (to avoid stucks)
                            bool sign = FVmath::calculateRandom(1,0);
                            addPos = { static_cast<float>(FVmath::calculateRandom(5, 0)), static_cast<float>(FVmath::calculateRandom(5, 0))};
                            if(!sign) addPos = addPos * -1;
                        }
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
                        //Clean the previous path in case it has
                        ent.AI->linearPath.clear();
                        //creates a path to the point and then uses followpath to run over the points
                        //Calculate the position of the enemy in the map representation
                        auto bounds       = ent.render->Sprite.getGlobalBounds();
                        auto& pos         = ent.physics->pos;
                        FVmath::Point2Di startGrid = gMan_.worldPositionToGrid(pos.x + bounds.width / 3, pos.y + bounds.height / 3);
                        
                        //Calculate the position of the goal in the map representation
                        auto& playerPos           = gMan_.getPlayer().physics->pos;
                        auto playerBounds         = gMan_.getPlayer().render->Sprite.getGlobalBounds();
                        FVmath::Point2Di goalGrid = gMan_.worldPositionToGrid(playerPos.x + playerBounds.width / 3, (playerPos.y + playerBounds.height / 3));
 
                        std::cout << "Player position:  " << playerPos << std::endl;

                        std::cout << "Goal Grid:  " << goalGrid << std::endl;

                        std::cout << "Start Grid: " << startGrid << std::endl;

                        //Calculate the points of the map representation to the real world
                        auto reversedGridPath = FVAI::findPathAStar(startGrid, goalGrid, gMan_.getMapGridRepresentation());
                        for (int i = reversedGridPath.size() - 1; i >= 0; --i) 
                        {
                            //std::cout << reversedGridPath[i] << std::endl;
                            //transform point to world position and add to the linear iterator
                            ent.AI->linearPath.addPoint(reversedGridPath[i] * tileSize);
                        }
                                            
                        if(ent.AI->linearPath.getPath().size() == 0) 
                        {
                            std::cout << "No se ha encontrado un camino, vuelve a comportamiento original" << std::endl; 
                            ent.AI->behaviour = ent.AI->originalBehaviour;
                        }
                        else
                        {
                            //change behaviour to follow path
                            //mainDepruebas(startGrid, goalGrid, gMan_.getMapGridRepresentation());
                            ent.AI->behaviour = FVAI::SB::FOLLOWPATH;
                        }
                        
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