#include "GameManager.hpp"
#include "utils/gameData.hpp"

#define PLAYER_SPRITE_PATH  "../resources/sprites.png"
#define HEARTH_PATH         "../media/HUD/heart.png"
#define COIN_PATH           "../media/HUD/coin.png"
#define CLOCK_PATH          "../media/HUD/clock.png"
#define SHIELD_SP_PATH      "../media/HUD/shield.png"
#define PET1_SP_PATH        "../media/pets/vitalis.png"
#define PET2_SP_PATH        "../media/pets/guardian.png"
#define PET3_SP_PATH        "../media/pets/sentinel.png"


namespace FVeng
{
        GameManager::GameManager(sf::RenderWindow& window)
        :window_ {window} 
        {}
        // : window_(sf::VideoMode(x, y), nameGame)
        // {
        //     window_.setKeyRepeatEnabled(true); // Habilitar entrada de teclado repetido
        //     window_.setFramerateLimit(60);
        // }

        [[nodiscard]] sf::RenderWindow& GameManager::getWindow()
        {
            return window_;
        }

        [[nodiscard]] FVeng::EntityManager<game::Entity>& GameManager::getEntityManager()
        {
            return EM_;
        }

        [[nodiscard]] game::blackBoardComponent& GameManager::getBB()
        {
            return bb_;
        }

        [[nodiscard]] tXMLeng::mapManager& GameManager::getMapManager()
        {
            return mapMan;
        }



        void GameManager::initLevel()
        {
            mapMan.InitMap("../media/Mapa2.tmx");
        }

        void GameManager::LoadAllTextures()
        {
            SPman.loadTexture(PLAYER_SPRITE_PATH, PLAYER_TEXT);
            SPman.loadTexture(mapMan.getTexturePath(), MAP_TEXT);
            SPman.loadTexture(HEARTH_PATH, HEART_TEXT);
            SPman.loadTexture(COIN_PATH, COIN_TEXT);
            SPman.loadTexture(CLOCK_PATH, CLOCK_TEXT);
            SPman.loadTexture("../media/bullet.png", BULLET_TEXT);
            SPman.loadTexture(PET1_SP_PATH, PET1_TEXT);
            SPman.loadTexture(PET2_SP_PATH, PET2_TEXT);
            SPman.loadTexture(PET3_SP_PATH, PET3_TEXT);
            SPman.loadTexture(SHIELD_SP_PATH, SHIELD_TEXT);
        }

        void GameManager::initGame()
        {
            initLevel();
            LoadAllTextures();
            createMap();
            createAllSpawner();
            auto& player = createPlayer({320,240});
            if(FVData::getSelectedPet() != -1)
            {
                createPet({320,240});
            }
            bb_.targetID = player.id();

        }

        [[maybe_unused]] game::Entity& GameManager::createPlayer(FVmath::Point2Di Pos)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);
            // Lo dispongo en el centro de la pantalla
            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .vel{0,0},.mov_speed =640/4};


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.input  = game::InputComponent{};

            e.weapon = game::WeaponComponent{};

            //health status 
            float life = 500;
            e.health = game::HealthComponent{ .maxLife = life, .currentLife = life, .inmortalityTime = 1 / 2};

            //add tag player
            e.addTag(game::Entity::TAG::Player); 

            //create life 
            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            //create data component
            int coins = FVData::getCoins();

            e.data   = game::DataComponent      {.coins = coins};

            e.shield = game::ShieldComponent    {.refreshTime = 6.f, .autoActive = false, .max_ActivatedTime = 1.5f};

            initEntityRender(e, {0,0}, sf::IntRect(0 * 75, 0 * 75, 75, 75));

            return e;
        }


        [[maybe_unused]] game::Entity& GameManager::createPet(FVmath::Point2Di Pos)
        {
            //Read the pet we must use
            int petNum = FVData::getSelectedPet();

            auto& e = EM_.createEntity();

            int texIdx = -1; 
            switch (petNum)
            {
                case 0:  texIdx = SPman.getTextureIdxByName(PET1_TEXT); break;
                case 1:  texIdx = SPman.getTextureIdxByName(PET2_TEXT); break;
                case 2:  texIdx = SPman.getTextureIdxByName(PET3_TEXT); break;
                default: break;
            }

            
            
            // Lo dispongo en el centro de la pantalla
            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .vel{0,0},.mov_speed =640/4};


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            if(petNum == 3)
            {
                e.weapon = game::WeaponComponent{};
            }
            

            //health status 
            float life = 200;
            e.health = game::HealthComponent{ .maxLife = life, .currentLife = life, .inmortalityTime = 1 / 2};

            //add tag player
            e.addTag(game::Entity::TAG::Pet); 

            //create life 
            if(texIdx != -1)
            {
                e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };
            }

            initEntityRender(e, {0,0}, sf::IntRect(0, 0, 32, 32));

            return e;
        }

        void GameManager::createMap()
        {
            auto& e = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);
            e.map = game::MapComponent { .texIndex=texIdx, .FVSprite{}, .maxLowerLayer=mapMan.getMaxBaseLayer() };

            e.map->FVSprite.assignTexture(&SPman.getTextureByName(MAP_TEXT));
            //mapMan.setActiveLayer(-1);         
            e.map->FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSizePath());
        }

        void GameManager::createEnemyArrive(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, double friction, double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/6 };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.AI     = game::AIComponent        { .targetCoord{targetCoord}, .behaviour=FVAI::SB::ARRIVE, .friction = friction, .time2arrive = 1 , .arrivalRadius = 2, .perceptionTime=perceptionTime}; 

            e.render  = game::RenderComponent   { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)}};

            e.reward = game::RewardComponent    {.min_reward = 1, .max_reward = 3};

            float life = 50;
            e.health = game::HealthComponent    { .maxLife = life, .currentLife = life, .inmortalityTime = 0};   

            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy); 

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(1 * 75, 1 * 75, 75, 75));             
        }

        void GameManager::createEnemyShoot(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID, double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/8 };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            ); 

            e.weapon    = game::WeaponComponent {};              

            e.AI        = game::AIComponent      { .targetCoord{targetCoord}, .behaviour =FVAI::SB::STAY, .targetID=targetID, .perceptionTime=perceptionTime};         
                                    
            e.render    = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            e.reward    = game::RewardComponent    {.min_reward = 2, .max_reward = 4};

            float life = 50;
            e.health    = game::HealthComponent    { .maxLife = life, .currentLife = life, .inmortalityTime = 0}; 

            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy); 

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(1 * 75, 0 * 75, 75, 75));
        }

        void GameManager::createBullet(FVmath::Point2Di Pos, FVmath::Point2Di Vel){

            auto& e = EM_.createEntity();

            e.physics = game::PhysicsComponent{ .pos{float(Pos.x)+30,float(Pos.y)+35}, .prevPos{float(Pos.x)+30,float(Pos.y)+35}, .vel{float(Vel.x),float(Vel.y)},.mov_speed =640/4};

            auto texIdx = SPman.getTextureIdxByName(BULLET_TEXT);
            std::cout <<  "NUM TEXTURA: " << texIdx << std::endl;

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{Pos.x,Pos.y}};

            initEntityRender(e, {0,0}, sf::IntRect(0 * 75, 0 * 75, 75, 75));

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            //Set player bullet
            e.addTag(game::Entity::TAG::Bullet);
            e.addTag(game::Entity::TAG::Player);
        }

        //Create all spawners on the current map
        void GameManager::createAllSpawner()
        {

            for(auto& spawner : mapMan.getSpawners())
                createSpawner(spawner);
            
        }

        //Creates a concrete instance of a Spawner
        void GameManager::createSpawner(tXMLeng::Spawner& spawner)
        {
            auto& e = EM_.createEntity();

            e.Spawn = game::SpawnerComponent{.SpawnInfo{spawner}};
        }

        //Loads next layer info in the Sprite, to change layer being drawn
        void GameManager::setRenderNextLayer(game::MapComponent& map)
        {
            int currentLayer = mapMan.getActiveLayer();
            currentLayer++;
            mapMan.setActiveLayer(currentLayer);
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSizePath());
        }

        //Called to reset Sprite info once all map layers have been drawn
        void GameManager::resetMap(game::MapComponent& map)
        {
            mapMan.setActiveLayer(0);
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSizePath());
        }


        void GameManager::createEnemyPursue(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/8 };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );               

            e.AI  = game::AIComponent      { .targetCoord{targetCoord}, .behaviour =FVAI::SB::PURSUE, .targetID=targetID, .perceptionTime=perceptionTime};         
                                    
            e.render  = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            e.reward = game::RewardComponent    {.min_reward = 2, .max_reward = 4};

            float life = 50;
            e.health = game::HealthComponent    { .maxLife = life, .currentLife = life, .inmortalityTime = 0}; 

            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy); 

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(1 * 75, 0 * 75, 75, 75));
        }

        void GameManager::SpawnDummy(FVmath::Point2Di Pos)
        {
            std::cout << "Spawn DUMMY" << std::endl;

            auto& e = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);
                        FVmath::Point2D position = {float(Pos.x),float(Pos.y)};

            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/4 };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );    

            e.render  = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            auto row = FVmath::calculateRandom(3,1);

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(row * 75, 1 * 75, 75, 75));


        }

        [[maybe_unused]] game::Entity&  GameManager::createHeart()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(HEART_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},sf::IntRect(0,0,38,30));

            return e;
        }

        [[maybe_unused]] game::Entity&  GameManager::createCoin()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(COIN_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},sf::IntRect(0,0,32,32));

            return e;
        }

        [[maybe_unused]] game::Entity&  GameManager::createClock()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(CLOCK_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},sf::IntRect(0,0,32,32));

            return e;
        }

        [[maybe_unused]] game::Entity&  GameManager::createShield()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(SHIELD_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},sf::IntRect(0,0,32,32));

            return e;
        }

        void GameManager::initEntityRender(game::Entity& entity, FVmath::Point2D origin, sf::IntRect TexRect)
        {
            //Y creo el spritesheet a partir de la imagen anterior
            SPman.assignTexture(entity.render->Sprite,entity.render->texIndex);
            //Le pongo el centroide donde corresponde
            SPman.modifySpriteOrigin(entity.render->Sprite, origin); //{75 / 2, 75 / 2}
            //Cojo el sprite que me interesa por defecto del sheet
            SPman.modifyTextureRect(entity.render->Sprite, TexRect); //sf::IntRect(0 * 75, 0 * 75, 75, 75));

        }

        game::Entity& GameManager::getPlayer()
        {
            for(auto& player : EM_)
            {
                if(player.input)
                {
                    return player;
                }
            }
        }



}