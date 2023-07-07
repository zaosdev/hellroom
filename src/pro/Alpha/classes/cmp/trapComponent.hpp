#pragma once 
#include <array>
#include <chrono>

namespace game
{
    enum estado
    {
        primero,segundo,tercero,cuarto
    };
    struct TrapComponent
    {
        estado modo{estado::primero};
        float delayTime {2};
        float trapDamage {100};
        std::chrono::steady_clock::time_point current_time{};
        std::chrono::seconds::rep elapsed_time{};
        std::chrono::steady_clock::time_point tiempo_comienzo_1{};

    };
}