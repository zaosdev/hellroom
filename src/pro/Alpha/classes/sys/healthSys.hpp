#pragma once

#include "../man/GameManager.hpp"
#include "../cmp/blackBoardComponent.hpp"
#include "../man/stateManager.hpp"
#include "../states/gameOverState.hpp"
// #include "../states/state.hpp"

namespace game
{
    struct HealthSys
    {
        HealthSys(FVeng::GameManager& gameMan, FVEng::StateMachine& stateMachine);

        HealthSys (const HealthSys&) = delete;
        HealthSys (HealthSys&&) = delete;
        HealthSys& operator=(const HealthSys&)= delete;
        HealthSys& operator=(HealthSys&&)= delete;

        void update(double dt);
        void applyPositive (std::optional<game::HealthComponent>&);
        void applyBoth     (std::optional<game::HealthComponent>&);
        void restartEffects(std::optional<game::HealthComponent>&);
        void setInmortality(std::optional<game::HealthComponent>&);
        void setMortality  (std::optional<game::HealthComponent>&);

        private:
            FVeng::GameManager&  gMan_;
            FVEng::StateMachine& SM_;
    };
}