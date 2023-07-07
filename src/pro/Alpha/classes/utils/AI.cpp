#include "AI.hpp"
#include "math.hpp"
#include <cmath>
#include <algorithm>

#include <iostream>
#include <assert.h>

FVmath::Point2D FVAI::arrive(FVmath::Point2D origin, FVmath::Point2D target, double MaxSpeed, double arrivalRadius = 2, double friction = 0, bool decreaseVelocity = false, double time2arrive = 1)
{
    //Calculate distance to the target
    double distance = std::hypot(origin.x - target.x, origin.y - target.y);
    
    if(distance <= arrivalRadius)
    {
        //std::cout << "No enough distance to do arrive" << std::endl;
        return {};
    }
    else
    {
        // std::cout << "Distance: " << distance<< std::endl;
        // std::cout << "Arrival radius:" << arrivalRadius << std::endl;
    }
    
    //Calculate the desired direction and angle
    double dirX = target.x - origin.x;
    double dirY = target.y - origin.y;
    double angle = atan2(dirY, dirX);

    //To simulate velocity reducction of arrive
    double currentSpeed;
    if(decreaseVelocity) currentSpeed = distance / time2arrive;
    else                 currentSpeed = MaxSpeed;
    currentSpeed = std::clamp(currentSpeed - friction * currentSpeed, 0.0, MaxSpeed);

    //Calculate movement using the angle
    double xMovement = currentSpeed * cos(angle);
    double yMovement = currentSpeed * sin(angle);

    return {float(xMovement), float(yMovement)};
}


FVmath::Point2D FVAI::seek(FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius = 2)
{
    return arrive(origin, target, speed, arrivalRadius);
}

FVmath::Point2D FVAI::pursue(FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius = 2)
{
    return seek(origin, target, speed, arrivalRadius); 
}

FVmath::Point2D FVAI::stay()
{
    return {};
}

FVmath::Point2D FVAI::flee(FVmath::Point2D origin, FVmath::Point2D target, double speed)
{
    return -seek(origin, target, speed); 
}

FVmath::Point2D FVAI::cross(FVAI::PriotiryCross priority, double speed)
{
    if(priority == FVAI::PriotiryCross::FIRSTX) return {float(speed), 0};
    else                                        return {0, float(speed)};
}

FVmath::Point2D FVAI::followCircularPath(FVmath::Point2D origin, circularIterator& path, double speed)
{
    auto addPos = seek(origin, path.getCurrent(), speed);
    if(addPos == FVmath::Point2D{}) path.getNext();
    return addPos;
}

FVmath::Point2D FVAI::followPath(FVmath::Point2D origin, linearIterator& path, double speed)
{
    auto addPos = seek(origin, {(float)path.getCurrent().x, (float)path.getCurrent().y}, speed, 5.f);
    std::cout << "addpos: " << addPos << std::endl;
    if(addPos == FVmath::Point2D{}) 
    {   
        if(path.getNext() == FVmath::Point2Di{-1,-1}) 
        {
            std::cout << "HA terminado el camino" << std::endl;
            //std::terminate();
        } 
        else
        {
            addPos = seek(origin, {(float)path.getCurrent().x, (float)path.getCurrent().y}, speed, 5.f);
        }
    }
    
    return addPos;
}


        void imprimirMapa(const std::vector<std::vector<int>>& mapRepresentation) {
        for (const auto& fila : mapRepresentation) {
            for (const auto& elemento : fila) {
                std::cout << elemento << " ";
            }
            std::cout << std::endl;
        }
    }


    const std::vector<FVmath::Point2Di> directions = {
        {0, -1},  // Up
        {0, 1},   // Down
        {-1, 0},  // Left
        {1, 0},   // Right
        // {-1, -1}, // Diagonal top left
        // {-1, 1},  // Diagonal bottom left
        // {1, -1},  // Diagonal top right
        // {1, 1}    // Diagonal bottom right
    };

    std::vector<FVmath::Point2Di> FVAI::findPathAStar     (FVmath::Point2Di start, FVmath::Point2Di goal, const std::vector<std::vector<int>>& map, int maxIteraciones)
    {
        const int mapWidth = map.size();
        const int mapHeight = map[0].size();

        auto deleteNodes = [&](std::vector<FVAI::PathNode*>& closedList, std::priority_queue<FVAI::PathNode*, std::vector<FVAI::PathNode*>, FVAI::CompareNodes>& openList) 
        {
            for (auto& node : closedList )
            {
                delete node;
            }

            while (!openList.empty()) 
            {
                FVAI::PathNode* node = openList.top();
                openList.pop();
                delete node;
            }
        };

        const std::vector<FVmath::Point2Di> directions = {
            {0, -1},  // Up
            {0, 1},   // Down
            {-1, 0},  // Left
            {1, 0},   // Right
            // {-1, -1}, // Diagonal top left
            // {-1, 1},  // Diagonal bottom left
            // {1, -1},  // Diagonal top right
            // {1, 1}    // Diagonal bottom right
        };

        //Sort the nodes accoding to compareElements function (the less value, the first)
        std::priority_queue<FVAI::PathNode*, std::vector<FVAI::PathNode*>, FVAI::CompareNodes> openList; //nodes to explore
        std::vector<FVAI::PathNode*> closedList;                                         //explored nodes

        FVAI::PathNode* startNode = new FVAI::PathNode(start.x, start.y, 0.f, 0.f, nullptr);
        openList.push(startNode);                                              //add the start node to the open list

        int iteraciones = 0;
        while (!openList.empty() && iteraciones < maxIteraciones)              //will theres a possible path
        {
            iteraciones++;
            //std::cout << "Iteracion: " << ++iteraciones << std::endl;
            FVAI::PathNode* currentNode = openList.top();                                //node to check is the first (ordered in priority queue)
            openList.pop();                                                    //eliminate the current element from the openlist             

            if (currentNode->x == goal.x && currentNode->y == goal.y)          //if the end node is found, return the path
            {
                std::vector<FVAI::PathNode*> path;
                FVAI::PathNode* pathNode = currentNode;
                while (pathNode != nullptr)                                    //whiles theres parents of the node, add to the path
                {
                    path.push_back(pathNode);
                    pathNode = pathNode->parent;
                }
                //Clean the memory and return the grid points
                std::vector<FVmath::Point2Di> pointPath {};
                for (auto& node : path)
                {
                    pointPath.push_back({node->x, node->y});
                    //     delete node; //no need to delete, they are on the closed list
                }
                deleteNodes(closedList, openList);


                return pointPath;
            }

            closedList.push_back(currentNode);                                //add the current node to the closed list

            for (const auto& direction : directions)                          //check on every direction
            {
                int nextX = currentNode->x + direction.x;
                int nextY = currentNode->y + direction.y;

                if 
                (     
                    nextX >= 0                    //valid in x       
                &&    nextX < mapWidth              //
                &&    nextY >= 0                    //valid in y
                &&    nextY < mapHeight             //
                &&    map[nextX][nextY] == 0        //can pass through ( valid node )
                )
                {
                    //diagonal movements would cost 15, normal movements (WASD) cost 10
                    float g = currentNode->g + std::sqrt(static_cast<float>(direction.x * direction.x + direction.y * direction.y))    * 10; 
                    float h = std::sqrt(static_cast<float>((nextX - goal.x) * (nextX - goal.x) + (nextY - goal.y) * (nextY - goal.y))) * 10; 

                    FVAI::PathNode* nextNode = new FVAI::PathNode(nextX, nextY, g, h, currentNode);

                    bool skipNode = false;
                    for (const auto& node : closedList) //check if the node is on the closed list to skip it
                    {
                        if (node->x == nextNode->x && node->y == nextNode->y)
                        {
                            skipNode = true;
                            break;
                        }
                    }

                    if (!skipNode)  //if the node is not skipped, add to the open list
                    {
                        openList.push(nextNode);
                    }
                }
            }
        }
    //Clean the used memory before sendin  void path
    deleteNodes(closedList, openList);
    return {}; //if theres no nodes left to check, return an empty path
}

