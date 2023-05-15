#pragma once
#include "../man/GameManager.hpp"
#include "../man/inputManager.hpp"
#include <iostream>

static constexpr char SHIELD_KEY = 'Q';


namespace game
{

    struct ShieldSys
    {
        ShieldSys(FVeng::GameManager& gameMan, InputManager& intpRec);

        ShieldSys (const ShieldSys&) = delete;
        ShieldSys (ShieldSys&&) = delete;
        ShieldSys& operator=(const ShieldSys&)= delete;
        ShieldSys& operator=(ShieldSys&&)= delete;

        void update(double dt);
        void activateShield(game::Entity& ent, bool restartTime);
       

        private:
            void check4Activation(game::Entity& ent, double dt);
            void activatedLogic  (game::Entity& ent, double dt);
            FVeng::GameManager& gMan_;
            InputManager&       inpRec_;
    };

}