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
#include "../classes/sys/rewardSys.hpp"
#include "../classes/sys/weaponSys.hpp"
#include "../classes/sys/petSys.hpp"
#include "../classes/sys/shieldSys.hpp"
#include "../classes/sys/effectSys.hpp"
#include "../classes/sys/roomSys.hpp"
#include "../classes/sys/trapSys.hpp"


#include "../classes/sys/animationSys.hpp"

#include "../man/stateManager.hpp"
#include "../states/gameOverState.hpp"

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
        , phySys        { GameMan }
        , inpRec        { window_ }
        , inpSys        { GameMan, inpRec, soundSys }
        , AISys         { GameMan }
        , healthSys     { GameMan }
        , spwnSys       { GameMan }
        , efctSys       { GameMan }
        , soundSys      { GameMan, inpRec }
        , achSys        { /*GameMan*/ }
        , saveSys       { GameMan }
        , collisionSys  { GameMan }
        , HudSys        { GameMan }
        , renSys        { GameMan, HudSys }
        , rewardSys     { GameMan }
        , weaponSys     { GameMan }
        , shieldSys     { GameMan, inpRec }
        , petSys        { GameMan, shieldSys }
        , roomSys       { GameMan}
        , animSys       { GameMan }
        , trapSys       { GameMan }
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
            spwnSys.SpawnPlayer();
            HudSys.setPlayer    (&GameMan.getPlayer());
            HudSys.setHeartID   (GameMan.createHeart().id());
            HudSys.setCoinID    (GameMan.createCoin().id());
            HudSys.setClockID   (GameMan.createClock().id());
            HudSys.setShieldID  (GameMan.createShield().id());
            petSys.initPetSys();
            soundSys.loadSounds();
            renSys.iniRenderSys();
            animSys.setTexureID (GameMan.getPlayer().id()); 
            //tendria que ser con el spritesheet completo y de ahi hacer recortes de cada animacion de sprite 
            
        }

        void changeLevel()
        {
            spwnSys.SpawnPlayer();
            GameMan.change_level=false;
        }

        void executeState() override
        {
            //Bucle del juego
            while (GameMan.getWindow().isOpen() && GameMan.getPlayer().health->currentLife > 0) 
            {
                //Bucle de obtención de eventos
                GameMan.update();
                GameMan.getEntityManager().update();
                if(GameMan.change_level)
                {
                    changeLevel();
                }
                if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
                {
                    double dt = updateClock.restart().asSeconds();


                    roomSys.update();

                    //IN THE FUTURE THIS MUST BE AFTER COLLSYS UPDATE, MAYBE NOT 
                    spwnSys.update();
                    trapSys.update();

                    inpRec.update();
                    inpSys.update();


                    AISys.update(GameMan.getBB(), dt);

                    phySys.update(dt);

                    petSys.update(dt);

                    shieldSys.update(dt);

                    collisionSys.update(dt);

                    efctSys.update(dt);

                    soundSys.update();

                    healthSys.update(dt);

                    weaponSys.update();

                    rewardSys.update();
                    //achSys.update();
                    saveSys.update();

                    animSys.update(dt /*updateClock.getElapsedTime().asSeconds()*/);
                
                }

                //std::cout << "updating render" << std::endl;
                // //Render game
                float percentTick = std::min(1.0, updateClock.getElapsedTime().asMilliseconds() / UPDATE_TICK_TIME); // ms / ms to get pt
                renSys.update(percentTick);

            }

            //player is dead
            SM_.AddState(std::make_unique<FVEng::gameOverState>(SM_.getWindow(), SM_), true);
        }


    

    private:
        sf::RenderWindow&   window_;
        FVEng::StateMachine& SM_;


        FVeng::GameManager      GameMan;
        game::PhysicsSys        phySys;
        game::InputManager      inpRec;
        game::InputSys          inpSys;
        game::AISys             AISys;
        game::HealthSys         healthSys;
        game::SpawnSys          spwnSys;
        game::effctSys          efctSys;
        game::SoundSys          soundSys;
        game::AchievementSys    achSys;
        game::SavingSys         saveSys;
        game::CollisionSys      collisionSys;
        game::HUDSys            HudSys;
        game::RenderSys         renSys;
        game::RewardSys         rewardSys;
        game::WeaponSys         weaponSys;
        game::ShieldSys         shieldSys;
        game::PetSys            petSys;
        game::RoomSys           roomSys;
        game::animationSys      animSys;
        game::TrapSys           trapSys;

  
        //Game clock
        sf::Clock clock;
        sf::Clock updateClock;
        double UPDATE_TICK_TIME = 1000 / 15; //15fps for the systems, 60 fps por the renders
    };
}
