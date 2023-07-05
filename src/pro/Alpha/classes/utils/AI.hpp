#pragma once

#include "AI.hpp"
#include "math.hpp"
#include "circularIterator.hpp"
#include "Pathfinding.hpp"
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

namespace FVAI
{
    enum class SB
    {
        STAY,
        ARRIVE,
        SEEK,
        PURSUE,
        FLEE,
        CROSSCREEN,
        FOLLOWPATH,
        SHOOTATTACK,
        PATHFINDING
    };

    enum class PriotiryCross
    {
        FIRSTX,
        FIRSTY
    };

    // struct PathNode
    // {
    //     int x;                  //x position
    //     int y;                  //y position
    //     float g;                //distance from the start node
    //     float h;                //distance from the end node
    //     float f;                //g + h
    //     PathNode* parent;       //reference to the parent node

    //     PathNode(int x_, int y_, float g_, float h_, PathNode* parent_)
    //         : x(x_), y(y_), g(g_), h(h_), f(g_ + h_), parent(parent_)
    //     {}
    // };

    // //compare the f cost of both nodes
    // struct CompareNodes
    // {
    //     bool operator()(const PathNode* node1, const PathNode* node2) //call operator, the function used on the queue
    //     {
    //         return node1->f > node2->f;
    //     }
    // };

    struct PathNode
{
    int x;
    int y;
    float g;  // Costo acumulado desde el nodo inicial hasta este nodo
    float h;  // Heurística estimada desde este nodo hasta el nodo objetivo
    float f;  // Suma de g y h
    PathNode* parent;

    PathNode(int _x, int _y, float _g, float _h, PathNode* _parent)
        : x(_x), y(_y), g(_g), h(_h), f(_g + _h), parent(_parent)
    {
    }
};

struct CompareNodes
{
    bool operator()(const PathNode* node1, const PathNode* node2)
    {
        return node1->f > node2->f;
    }
};


    FVmath::Point2D arrive                (FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius, double friction, bool decreaseVelocity, double time2arrive);
    FVmath::Point2D stay                  ();
    FVmath::Point2D seek                  (FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius);
    FVmath::Point2D pursue                (FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius);
    FVmath::Point2D flee                  (FVmath::Point2D origin, FVmath::Point2D target, double speed);
    FVmath::Point2D cross                 (FVAI::PriotiryCross priority, double speed);
    FVmath::Point2D followPath            (FVmath::Point2D origin, circularIterator& path, double speed);
    std::vector<FVAI::PathNode*> findPathAStar(FVmath::Point2Di start, FVmath::Point2Di goal, const std::vector<std::vector<int>>& map);
}