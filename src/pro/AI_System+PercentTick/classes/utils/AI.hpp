#pragma once

#include "utils/AI.hpp"
#include "math.hpp"
#include "utils/types.hpp"
#include "utils/circularIterator.hpp"

namespace FVAI
{
    enum class SB
    {
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

    FVmath::Point2D arrive      (FVmath::Point2D origin, FVmath::Point2D target, double speed, double friction); //the higher friction the slower will move on arriving
    FVmath::Point2D seek        (FVmath::Point2D origin, FVmath::Point2D target, double speed);
    FVmath::Point2D pursue      (FVmath::Point2D origin, FVmath::Point2D target, double speed);
    FVmath::Point2D flee        (FVmath::Point2D origin, FVmath::Point2D target, double speed);
    FVmath::Point2D cross       (FVAI::PriotiryCross priority, double speed);
    FVmath::Point2D followPath  (FVmath::Point2D origin, circularIterator& path, double speed);
}