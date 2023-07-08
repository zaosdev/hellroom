#pragma once 

namespace game
{
    struct LeverComponent
    {
        bool pressed{false};
        std::size_t ownerID{0};

    };
}