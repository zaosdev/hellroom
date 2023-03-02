#pragma once

#include "../man/GameManager.hpp"



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
        void update(int, int);


        private:
            FVeng::GameManager& gMan_;
    };
}