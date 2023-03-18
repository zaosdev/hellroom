#pragma once

#include "utils/AI.hpp"
#include "math.hpp"

namespace FVAI
{
    enum class SB
    {
        ARRIVE,
        SEEK
    };

    FVmath::Point2D arrive(FVmath::Point2D origin, FVmath::Point2D target, double speed);

}