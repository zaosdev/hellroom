#pragma once

#include "../man/GameManager.hpp"
#include "../cmp/blackBoardComponent.hpp"
#include "../define.h"

namespace game
{
    struct AISys
    {
        AISys(FVeng::GameManager& gameMan);

        AISys (const AISys&) = delete;
        AISys (AISys&&) = delete;
        AISys& operator=(const AISys&)= delete;
        AISys& operator=(AISys&&)= delete;

        void update(blackBoardComponent bb, double dt);
        bool perception(std::optional<game::AIComponent>& AI, FVeng::EntityManager<game::Entity>& EM, blackBoardComponent& bb, double const dt);

        private:
            FVeng::GameManager& gMan_;
            static constexpr float MAX_DISTANCE {12 * tileSize}; //x tiles
    };
}