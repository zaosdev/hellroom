#pragma once

#include "../man/GameManager.hpp"
#include "../utils/gameData.hpp"
#include "shieldSys.hpp"

#define amplitude      20
#define frequency       5
#define displacement_x 60
#define displacement_y -20


namespace game
{
    struct PetSys
    {
        PetSys(FVeng::GameManager& gameMan, game::ShieldSys& shieldSys);
        ~PetSys();

        PetSys (const PetSys&) = delete;
        PetSys (PetSys&&) = delete;
        PetSys& operator=(const PetSys&)= delete;
        PetSys& operator=(PetSys&&)= delete;

        void initPetSys();
        void update(double dt);


        private:
            FVeng::GameManager& gMan_;
            game::ShieldSys& ssys_;
            double totalTime_ = 0.0;
            double clockTime_ = 0;
            sf::Clock clock_;
            int    petNum_    = -1;
    };
}