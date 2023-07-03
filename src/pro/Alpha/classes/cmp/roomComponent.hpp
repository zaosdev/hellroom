#pragma once 

#include "../utils/map_types.hpp"

namespace game
{

    struct RoomComponent
    {
        size_t ownerID{};
        tXMLeng::Room roomInfo{};
    };
}