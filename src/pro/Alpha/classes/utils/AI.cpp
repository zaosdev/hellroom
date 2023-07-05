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

FVmath::Point2D FVAI::followPath(FVmath::Point2D origin, std::vector<FVAI::PathNode>& path, double speed)
{
    (void) origin;
    (void) path;
    (void) speed;
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

std::vector<FVAI::PathNode> FVAI::findPathAStar(FVmath::Point2Di start, FVmath::Point2Di goal, const std::vector<std::vector<int>>& map, int& i)
{
    static int constexpr maxIterations = 500;

    std::cout << "Tamaño del mapa: " << map.size() << " x " << map[0].size() << std::endl;
    assert(!map.empty() && !map[0].empty()); // Assert map is not empty

    const int mapWidth = map.size();
    const int mapHeight = map[0].size();
    std::cout << "Tamaño del mapa: " << map.size() << " x " << map[0].size() << std::endl;

    const std::vector<FVmath::Point2Di> directions = {
        {0, -1},  // Up
        {0, 1},   // Down
        {-1, 0},  // Left
        {1, 0},   // Right
    };

    auto compareNodes = [](const FVAI::PathNode& node1, const FVAI::PathNode& node2) {
        return node1.f > node2.f;
    };

    std::priority_queue<FVAI::PathNode, std::vector<FVAI::PathNode>, decltype(compareNodes)> openList(compareNodes); // Nodes to explore       
    std::vector<FVAI::PathNode> closedList;                                                                          // Explored nodes                             

    FVAI::PathNode startNode(start.x, start.y, 0.f, 0.f, nullptr);
    openList.push(startNode);

    while (!openList.empty())
    {
        if (i > maxIterations)
            break;
        i++;

        FVAI::PathNode currentNode = openList.top();
        openList.pop();

        if (currentNode.x == goal.x && currentNode.y == goal.y)
        {
            std::vector<FVAI::PathNode> path;
            FVAI::PathNode pathNode = currentNode;
            while (pathNode.parent != nullptr)
            {
                path.push_back(pathNode);
                pathNode = *pathNode.parent;
            }
            path.push_back(pathNode);
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedList.push_back(currentNode);

        for (const auto& direction : directions)
        {
            int nextX = currentNode.x + direction.x;
            int nextY = currentNode.y + direction.y;

            if (nextX >= 0 && nextX < mapWidth && nextY >= 0 && nextY < mapHeight && map[nextX][nextY] == 0)
            {
                float g = currentNode.g + std::sqrt(static_cast<float>(direction.x * direction.x + direction.y * direction.y)) * 10;
                float h = std::sqrt(static_cast<float>((nextX - goal.x) * (nextX - goal.x) + (nextY - goal.y) * (nextY - goal.y)));
                FVAI::PathNode nextNode(nextX, nextY, g, h, &closedList.back());

                bool skipNode = false;
                for (const auto& node : closedList)
                {
                    if (node.x == nextNode.x && node.y == nextNode.y)
                    {
                        skipNode = true;
                        break;
                    }
                }

                if (!skipNode)
                {
                    openList.push(nextNode);
                }
            }
        }
    }

    std::cout << "No path found" << std::endl;
    return std::vector<FVAI::PathNode>(); // Return an empty vector if no path is found
}
