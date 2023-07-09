#pragma once 

namespace game
{
    
    enum boss_state
    {
        idle            = 1 << 0,
        melee_attack    = 1 << 1,
        laser_attack    = 1 << 2,
        dead            = 1 << 3,
        invincible      = 1 << 4,
        empty           = 1 << 5,

    };

    enum laser_state
    {
        charge          = 1 << 0,
        attack          = 1 << 1,

    };

    struct BossComponent{

        boss_state currentState{idle};
        boss_state pastState{idle};
        boss_state nextState{idle};

        float minDelay2nextState{0};
        laser_state currentLaserState{charge};
    };
}