#pragma once 


namespace game
{
    struct Entity;

    struct blackBoardComponent
    {
        bool         tActive {true};      
        Entity::id_type targetID;
    };
}