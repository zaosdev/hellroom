#pragma once

#include "../man/GameManager.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"

namespace game
{
    struct AchievementSys
    {
        AchievementSys(FVeng::GameManager& gameMan);
        ~AchievementSys();

        AchievementSys (const AchievementSys&) = delete;
        AchievementSys (AchievementSys&&) = delete;
        AchievementSys& operator=(const AchievementSys&)= delete;
        AchievementSys& operator=(AchievementSys&&)= delete;

        //void iniPhysicsSys();
        void update(Entity& player);
        void showPic();


        private:
            FVeng::GameManager& gMan_;
            SFMLeng::SpriteManager SPman{};
            //game::RenderSys renSys{gMan_};
    };
}