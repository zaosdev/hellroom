#pragma once
#include <iostream>

#include "../classes/sys/renderSys.hpp"
#include "../classes/sys/physicsSys.hpp"
#include "../classes/sys/inputSys.hpp"
#include "../classes/sys/soundSys.hpp"
#include "../classes/sys/achievementSys.hpp"
#include "../classes/sys/savingSys.hpp"
#include "../classes/man/GameManager.hpp"
#include "../classes/man/inputManager.hpp"
#include "../classes/sys/AISys.hpp"
#include "../classes/sys/spawnSys.hpp"
#include "../classes/sys/healthSys.hpp"
#include "../classes/sys/HUDSys.hpp"
#include "../classes/sys/collisionSys.hpp"

#include "../classes/man/stateManager.hpp"

#include "../utils/circularIterator.hpp"
#include "../cmp/blackBoardComponent.hpp"

#define MAX_NUMBER_OF_ITEMS 3

namespace FVEng{
    class gameState : public State {
    public:
        gameState(sf::RenderWindow& window, FVEng::StateMachine& SM)
        : window_       { window }
        , SM_           { SM }
        , GameMan       { window_ }
        , SPman         {}
        , phySys        { GameMan }
        , inpRec        { window_ }
        , inpSys        { GameMan, inpRec }
        , AISys         { GameMan }
        , healthSys     { GameMan }
        , spwnSys       { GameMan }
        , soundSys      { GameMan, inpRec }
        , achSys        { GameMan }
        , saveSys       { GameMan }
        , collisionSys  { GameMan }
        , HudSys        { GameMan }
        , renSys        { GameMan, HudSys }
        , clock         {}
        , updateClock   {}
        , UPDATE_TICK_TIME{ 1000 / 15 } 
        {
            //Init(); Init is automatically executed by the state machine
            std::cout << "Game init correctly" << std::endl;
        }

        void Init() override 
        {
            //create the player and update(needed fot the hud)
            GameMan.initGame();
            GameMan.getEntityManager().update();
            HudSys.setPlayer(&GameMan.getPlayer());
            HudSys.setHeartID(GameMan.createHeart().id());
            //soundSys.loadSound();
        }

        void executeState() override
        {
            //Bucle del juego
            while (GameMan.getWindow().isOpen()) 
            {
                //Bucle de obtención de eventos
                GameMan.getEntityManager().update();
                if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
                {
                double dt = updateClock.restart().asSeconds();

                inpRec.update();
                inpSys.update();

                AISys.update(GameMan.getBB(), dt);

                phySys.update(dt);

                collisionSys.update();

                //IN THE FUTURE THIS MUST BE AFTER COLLSYS UPDATE
                spwnSys.update();

                //soundSys.update();

                healthSys.update(dt);
                //achSys.update();
                //saveSys.update();
                }

                //std::cout << "updating render" << std::endl;
                // //Render game
                float percentTick = std::min(1.0, updateClock.getElapsedTime().asMilliseconds() / UPDATE_TICK_TIME); // ms / ms to get pt
                renSys.update(percentTick);
            }
        }


    

    private:
        sf::RenderWindow&   window_;
        FVEng::StateMachine& SM_;

        FVeng::GameManager      GameMan;
        SFMLeng::SpriteManager  SPman;
        game::PhysicsSys        phySys;
        game::InputManager      inpRec;
        game::InputSys          inpSys;
        game::AISys             AISys;
        game::HealthSys         healthSys;
        game::SpawnSys          spwnSys;
        game::SoundSys          soundSys;
        game::AchievementSys    achSys;
        game::SavingSys         saveSys;
        game::CollisionSys      collisionSys;
        game::HUDSys            HudSys;
        game::RenderSys         renSys;
        //Game clock
        sf::Clock clock;
        sf::Clock updateClock;
        double UPDATE_TICK_TIME = 1000 / 15; //15fps for the systems, 60 fps por the renders
    };
}
