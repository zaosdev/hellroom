#pragma once

#include "../man/GameManager.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"

namespace game
{
    struct SavingSys
    {
        SavingSys(FVeng::GameManager& gameMan);
        ~SavingSys();

        SavingSys (const SavingSys&) = delete;
        SavingSys (SavingSys&&) = delete;
        SavingSys& operator=(const SavingSys&)= delete;
        SavingSys& operator=(SavingSys&&)= delete;

        //void iniPhysicsSys();
        void update(Entity& player);
        std::array<int, 2> read();


        private:
            FVeng::GameManager& gMan_;
            SFMLeng::SpriteManager SPman{};
            game::RenderSys renSys{gMan_};
    };
}