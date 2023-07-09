#pragma once
#include <iostream>

#include "../classes/sys/renderSys.hpp"
#include "../classes/sys/physicsSys.hpp"
#include "../classes/sys/inputSys.hpp"
//#include "../classes/sys/soundSys.hpp"
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
#include "../classes/sys/cofreSys.hpp"
#include "../classes/sys/roomSys.hpp"
#include "../classes/sys/trapSys.hpp"
#include "../classes/sys/leverSys.hpp"

#include "../classes/sys/animationSys.hpp"

#include "../man/stateManager.hpp"

#include "../utils/circularIterator.hpp"
#include "../cmp/blackBoardComponent.hpp"

namespace FVEng{
    class gameState : public State {
    public:
        gameState(sf::RenderWindow& window, FVEng::StateMachine& SM)
        : window_       { window }
        , SM_           { SM }
        , GameMan       { window_ }
        , phySys        { GameMan }
        , inpRec        { window_ }
        , dialogueSys   { GameMan }
        , inpSys        { GameMan, inpRec, soundSys, dialogueSys }
        , AISys         { GameMan, soundSys }
        , healthSys     { GameMan }
        , spwnSys       { GameMan }
        , efctSys       { GameMan }
        , soundSys      { GameMan, inpRec }
        , achSys        { /*GameMan*/ }
        , saveSys       { GameMan }
        , collisionSys  { GameMan, soundSys }
        , HudSys        { GameMan }
        , renSys        { GameMan, HudSys, dialogueSys }
        , rewardSys     { GameMan }
        , weaponSys     { GameMan }
        , cofreSys      { GameMan, soundSys }
        , shieldSys     { GameMan, inpRec }
        , petSys        { GameMan, shieldSys }
        , roomSys       { GameMan}
        , animSys       { GameMan }
        , trapSys       { GameMan }
        , leverSys      { GameMan, soundSys }
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
            HudSys.setGunCruzID (GameMan.createGunCruz().id());
            HudSys.setGunEscopetaID (GameMan.createGunEscopeta().id());
            HudSys.setGunRafagaID (GameMan.createGunRafaga().id());
            // HudSys.setWeapon1ID (GameMan.createWeapon1().id());
            // HudSys.setWeapon2ID (GameMan.createWeapon2().id());
            // HudSys.setWeapon3ID (GameMan.createWeapon3().id());
            petSys.initPetSys();
            soundSys.loadSounds();
            //soundSys.initMusic = true;
            renSys.iniRenderSys();
            animSys.setTexureID (GameMan.getPlayer().id()); 
            //tendria que ser con el spritesheet completo y de ahi hacer recortes de cada animacion de sprite 
            renSys.startOnPlayer();
            dialogueSys.activateDialogue("1.1");
        }

        void changeLevel()
        {
            
            if(cambialvl == true){//este if es solo por el soundsys
                //colocar sonido
                soundSys.setLoop(false, soundSys.soundLevel);
                soundSys.playSound(soundSys.soundLevel, soundSys.isChangeLvl);

                std::cout << "change level" << std::endl;
                spwnSys.SpawnPlayer();
                GameMan.change_level=false;
                renSys.startOnPlayer();
                dialogueSys.activateDialogue("2.1");
                cambialvl = false;
            }
            else{
               // soundSys.setLoop(false, soundSys.soundLevel);
                soundSys.stopSound(soundSys.soundLevel, soundSys.isChangeLvl);
                cambialvl = true;
            }


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

                    leverSys.update();

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

                    cofreSys.update();

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
            //colocar sonido
            soundSys.setLoop(false, soundSys.soundGameOver);
            soundSys.playSound(soundSys.soundGameOver, soundSys.isGameOver);
            SM_.ChangeToGameOverState(true);
            //soundSys.stopSound(soundSys.soundGameOver, soundSys.isGameOver);
        }


    

    private:
        sf::RenderWindow&   window_;
        FVEng::StateMachine& SM_;


        FVeng::GameManager      GameMan;
        game::PhysicsSys        phySys;
        game::InputManager      inpRec;
        game::DialogueSys       dialogueSys;
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
        game::CofreSys          cofreSys;
        game::ShieldSys         shieldSys;
        game::PetSys            petSys;
        game::RoomSys           roomSys;
        game::animationSys      animSys;
        game::TrapSys           trapSys;
        game::LeverSys          leverSys;
  
        //Game clock
        sf::Clock clock;
        sf::Clock updateClock;
        double UPDATE_TICK_TIME = 1000 / 15; //15fps for the systems, 60 fps por the renders
        bool cambialvl = true;
    };
}
