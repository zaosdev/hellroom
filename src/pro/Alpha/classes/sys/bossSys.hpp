#pragma once

#include "../man/GameManager.hpp"

namespace game
{

    struct BossSys
    {
        BossSys(FVeng::GameManager& gameMan/*, SFMLeng::SpriteManager& spriteMan*/);
        ~BossSys();

        BossSys (const BossSys&) = delete;
        BossSys (BossSys&&) = delete;
        BossSys& operator=(const BossSys&)= delete;
        BossSys& operator=(BossSys&&)= delete;
   
        void update(float dt);

        void updateLaser(game::Entity& e,float dt);

        void initNewState(game::Entity& e);

        void updateCurrentState(game::Entity& e);


        private:
            FVeng::GameManager& gMan_;
            std::size_t laserId_    {0};
            std::size_t laserSprite_ {0};

            
    };
}