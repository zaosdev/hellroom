#include "roomSys.hpp"

namespace game
{
    RoomSys::RoomSys(FVeng::GameManager& Gman)
    : gMan_(Gman)
    {
    }

    void RoomSys::enableRoom(Entity& e)
    {
        gMan_.instantiateRoom(e.room->roomInfo,e.id());
    }

    bool RoomSys::isRoomCompleted(game::Entity& room)
    {
        for (auto id : room.room->room_enemies)
        {
            if(gMan_.getEntityManager().getEntityByID(id)->alive()) return false;
        }

        return true;
    }


    void RoomSys::update()
    {
        //check if it's a valid entity
        auto valid = [](Entity const& e){ return e.alive() && e.room && e.hasTag(game::Entity::TAG::ROOM);};

        auto isRoomTriggered = [&](Entity const& e){ return valid(e) && e.room->enabled==true;};
        
        auto RoomInitialized = [&](Entity const& e){ return e.room->initialized==true;};


        for(auto& e : gMan_.getEntityManager())
        {

            if(isRoomTriggered(e))
            {
                if(not RoomInitialized(e))  { enableRoom(e); }
                else                        { if(isRoomCompleted(e)) deleteRoom_=true; room2Delete_=e.id(); }
            }

        }

        if(deleteRoom_) { gMan_.roomDelete(room2Delete_); }
    }
}