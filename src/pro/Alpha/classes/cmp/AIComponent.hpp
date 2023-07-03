#pragma once 
#include "../utils/math.hpp"
#include "../utils/AI.hpp"
#include "../utils/circularIterator.hpp"

namespace game
{

    enum enemy_type
    {
        PURSUE = 1 << 0,
        SHOOT  = 1 << 1,
        ARRIVE = 1 << 2,
        NO_TYPE   = 1 << 3,
    };

    struct AIComponent
    {
        FVmath::Point2D                 targetCoord;                    //get position for arriving
        FVAI::SB                        behaviour;                      //behaviour of entity
        double                          friction;                       //slowing component for certain behaviours such as arrive
        uint32_t                        targetID;                       //look at the player
        double                          time2arrive    {1};             //for slowing on arrival
        double                          arrivalRadius  {10};             //tolerance
        FVAI::PriotiryCross             priotiryCross;                  //for behaviour that cross the window such as arriveRect and Crosscreen   
        FVAI::circularIterator          path;                           //usar std::vector para almacenar la ruta
        double                          perceptionTime {1};             //time 2 check the world
        double                          accumulatedTime{0};             //time passed to check
        double                          maxTimeAlive   {-1};            //-1 indicates never dies by time
        double                          timeAlive      {0};
        enemy_type                      type{enemy_type::NO_TYPE}; 
    };
}