#pragma once 

#include "../utils/FVSprite.hpp"




namespace game
{
    enum  map_object_t
    {
        MAP = 1<< 0,
        WALL = 1<< 1,
        DOOR = 1<< 2,
        EMPTY = 1<< 3,
    };


    struct MapComponent 
    {
        int texIndex{};
        sfml_util::FVSprite FVSprite{};
        int maxLowerLayer{0};
        map_object_t object_type{map_object_t::EMPTY}; 
        bool canOpen{false};
        std::string nextLevel{""};


    };
}