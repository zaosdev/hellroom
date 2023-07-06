#pragma once

#include "../man/GameManager.hpp"
#include "../utils/random.hpp"
#include "../utils/math.hpp"


namespace game
{
    struct RoomSys
    {
        RoomSys(FVeng::GameManager& Gman);
        ~RoomSys() = default;

        RoomSys (const RoomSys&) = delete;
        RoomSys (RoomSys&&) = delete;
        RoomSys& operator=(const RoomSys&)= delete;
        RoomSys& operator=(RoomSys&&)= delete;

        void enableRoom(game::Entity& room);

        bool isRoomCompleted(game::Entity& room);

        void update();

        private:
            FVeng::GameManager& gMan_;
            bool deleteRoom_{false};
            game::Entity::id_type room2Delete_{0};
    };
}