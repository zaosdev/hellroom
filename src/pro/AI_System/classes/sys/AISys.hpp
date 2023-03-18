#pragma once

#include "../man/GameManager.hpp"

namespace game
{
    struct AISys
    {
        AISys(FVeng::GameManager& gameMan);
        void update();

        private:
            FVeng::GameManager& gMan_;
    };
}