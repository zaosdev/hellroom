#pragma once 
#include "../utils/math.hpp"
#include "../utils/AI.hpp"
#include "../utils/types.hpp"
#include "../utils/circularIterator.hpp"

namespace game
{
    struct Entity; // Forward declaration de la estructura Entity
    struct AIComponent
    {
        FVmath::Point2D                 targetCoord;        //get position for arriving
        FVAI::SB                        behaviour;          //behaviour of entity
        double                          friction;           //slowing component for certain behaviours such as arrive
        EntityIDType                    targetID;           //look at the player
        FVAI::PriotiryCross             priotiryCross;      //for behaviour that cross the window such as arriveRect and Crosscreen   
        FVAI::circularIterator          path;               //usar std::vector para almacenar la ruta
        double                          perceptionTime {10}; //time 2 check the world
        double                          accumulatedTime;    //time passed to check
    };
}