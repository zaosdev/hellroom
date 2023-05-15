#pragma once

#include "../man/GameManager.hpp"
#include "../cmp/blackBoardComponent.hpp"

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
    };
}