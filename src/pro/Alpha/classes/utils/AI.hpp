#pragma once

#include "AI.hpp"
#include "math.hpp"
#include "circularIterator.hpp"

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
        FOLLOWPATH
    };

    enum class PriotiryCross
    {
        FIRSTX,
        FIRSTY
    };

    FVmath::Point2D arrive      (FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius, double friction, bool decreaseVelocity, double time2arrive);
    FVmath::Point2D stay        ();
    FVmath::Point2D seek        (FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius);
    FVmath::Point2D pursue      (FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius);
    FVmath::Point2D flee        (FVmath::Point2D origin, FVmath::Point2D target, double speed);
    FVmath::Point2D cross       (FVAI::PriotiryCross priority, double speed);
    FVmath::Point2D followPath  (FVmath::Point2D origin, circularIterator& path, double speed);
}