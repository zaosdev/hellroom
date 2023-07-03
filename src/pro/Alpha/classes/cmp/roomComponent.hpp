#pragma once 

#include "../utils/map_types.hpp"

namespace game
{

    struct RoomComponent
    {
        size_t ownerID{};
        tXMLeng::Room roomInfo{};
        bool enabled{false};
        bool initialized{false};
        std::vector<game::Entity::id_type> room_enemies{};

    };
}