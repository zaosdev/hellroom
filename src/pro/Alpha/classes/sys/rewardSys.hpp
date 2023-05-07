#pragma once

#include "../man/GameManager.hpp"
#include "utils/random.hpp"

namespace game
{
    struct RewardSys
    {
        RewardSys(FVeng::GameManager& gameMan);
        ~RewardSys();

        RewardSys (const RewardSys&) = delete;
        RewardSys (RewardSys&&) = delete;
        RewardSys& operator=(const RewardSys&)= delete;
        RewardSys& operator=(RewardSys&&)= delete;

        void update();

        private:
            FVeng::GameManager& gMan_;
    };
}