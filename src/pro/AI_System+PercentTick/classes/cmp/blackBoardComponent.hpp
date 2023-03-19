#pragma once 
#include "../utils/types.hpp"

namespace game
{
    struct blackBoardComponent
    {
        bool         tActive {true};      
        EntityIDType targetID;
    };
}