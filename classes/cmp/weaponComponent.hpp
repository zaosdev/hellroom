#pragma once 
#include <array>

namespace game
{
    enum directionType
    {
        norte,sur,este,oeste
    };
    enum mejora
    {
        normal,escopeta,cruz,rafaga
    };
    struct WeaponComponent
    {
        bool on{false};
        directionType direction{};
        mejora especial{mejora::normal};
        mejora current{mejora::normal};

    };
}