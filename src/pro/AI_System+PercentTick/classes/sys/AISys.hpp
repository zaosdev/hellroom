#pragma once

#include "../man/GameManager.hpp"
#include "../cmp/blackBoardComponent.hpp"

namespace game
{
    struct AISys
    {
        AISys(FVeng::GameManager& gameMan);
        void update(blackBoardComponent bb, double dt);
        void perception(std::optional<game::AIComponent>& AI, FVeng::EntityManager<game::Entity>& EM, blackBoardComponent& bb, double const dt);

        private:
            FVeng::GameManager& gMan_;
    };
}