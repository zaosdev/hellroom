#include "GameManager.hpp"
#include "cmp/CollisionComponent.hpp"
#include "utils/gameData.hpp"
#include "../define.h"

#define ENEMYA_SPRITE_PATH  "../media/player_enemy/wizard_attack.png"
#define ENEMYB_SPRITE_PATH  "../media/player_enemy/enemy_botaV.png"

static constexpr const char* PLAYER_SPRITE_PATH { "../media/player_enemy/player.png"};
static constexpr const char* HEARTH_PATH        { "../media/HUD/heart.png"};
static constexpr const char* COIN_PATH          { "../media/HUD/coin.png"};
static constexpr const char* CLOCK_PATH         { "../media/HUD/clock.png"};
static constexpr const char* SHIELD_SP_PATH     { "../media/HUD/shield.png"};
static constexpr const char* PET1_SP_PATH       { "../media/pets/vitalis.png"};
static constexpr const char* PET2_SP_PATH       { "../media/pets/guardian.png"};
static constexpr const char* PET3_SP_PATH       { "../media/pets/sentinel.png"};
static constexpr const char* BULLET_PATH        { "../media/bullet.png"};



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

        void GameManager::LoadAllTextures()
        {
            SPman.loadTexture(PLAYER_SPRITE_PATH, PLAYER_TEXT);
            SPman.loadTexture(ENEMYA_SPRITE_PATH, ENEMY_A);
            SPman.loadTexture(ENEMYB_SPRITE_PATH, ENEMY_B);
            SPman.loadTexture(HEARTH_PATH, HEART_TEXT);
            SPman.loadTexture(COIN_PATH, COIN_TEXT);
            SPman.loadTexture(CLOCK_PATH, CLOCK_TEXT);
            SPman.loadTexture(BULLET_PATH, BULLET_TEXT);
            SPman.loadTexture(PET1_SP_PATH, PET1_TEXT);
            SPman.loadTexture(PET2_SP_PATH, PET2_TEXT);
            SPman.loadTexture(PET3_SP_PATH, PET3_TEXT);
            SPman.loadTexture(SHIELD_SP_PATH, SHIELD_TEXT);
        }

        void GameManager::initGame()
        {
            LoadLevel();
            LoadAllTextures();
            createPlayer({320,240});
            if(FVData::getSelectedPet() != -1)
            {
                createPet({320,240});
            }

        }

        [[maybe_unused]] game::Entity& GameManager::createPlayer(FVmath::Point2Di Pos)
        {
            auto& e = EM_.createEntity();

            setPlayerID(e.id());
            bb_.targetID = e.id();

            auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);
            // Lo dispongo en el centro de la pantalla

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

            e.render->Sprite.setScale(2.5,2.75);

            initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(128, 112,16,16));

            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .vel{0,0},.mov_speed =640/4, .size{e.render->Sprite.getGlobalBounds().height ,e.render->Sprite.getGlobalBounds().width}};

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.coll = game::CollisionComponent{};

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
            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .vel{0,0},.mov_speed =640.0/4};


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );
            
            //if(petNum == 0)   //VITALIS

            if(petNum == 1)     //Guardian
            {
                e.shield = game::ShieldComponent{.refreshTime = 4.f, .autoActive = true , .max_ActivatedTime = 2.f};
            } 
            // else if(petNum == 2) //Sentinel
            // {}
            

            //health status 
            float life = 200;
            e.health = game::HealthComponent{ .maxLife = life, .currentLife = life, .inmortalityTime = float(1/2)};

            //add tag player
            e.addTag(game::Entity::TAG::Pet); 

            //create life 
            if(texIdx != -1)
            {
                e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };
            }

            initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(0, 0, 32, 32));

            return e;
        }

        void GameManager::createMap()
        {
            auto& e = EM_.createEntity();
            mapID_ = e.id();
            auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);
            e.map = game::MapComponent { .texIndex=texIdx, .FVSprite{}, .maxLowerLayer=mapMan.getMaxBaseLayer(), .object_type= game::map_object_t::MAP};

            e.map->FVSprite.assignTexture(&SPman.getTextureByName(MAP_TEXT));
            //mapMan.setActiveLayer(-1);         
            e.map->FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSize());

            for(auto posColl : mapMan.getColliderData())
            {
                createMapCollider(posColl);
            }
        }

        void GameManager::changeMap()
        {
            auto& e = *EM_.getEntityByID(mapID_);

            auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);
            e.map = game::MapComponent { .texIndex=texIdx, .FVSprite{}, .maxLowerLayer=mapMan.getMaxBaseLayer(), .object_type= game::map_object_t::MAP };

            e.map->FVSprite.assignTexture(&SPman.getTextureByName(MAP_TEXT));
            //mapMan.setActiveLayer(-1);         
            e.map->FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSize());

            for(auto posColl : mapMan.getColliderData())
            {
                createMapCollider(posColl);
            }
        }

        [[maybe_unused]] game::Entity& GameManager::createMapCollider(FVmath::Point2Di Pos)
        {
            auto& e = EM_.createEntity();

            //auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);


            e.map = game::MapComponent { .texIndex=-1, .FVSprite{}, .maxLowerLayer=-1, .object_type= game::map_object_t::WALL };

            e.coll = game::CollisionComponent{};           

            e.addTag(game::Entity::TAG::STATIC_COLL);

            // e.render  = game::RenderComponent   { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)}};

            // initEntityRender(e,{0,0},SFMLeng::SpriteManager::rect_i_type(2 * 16, 12 * 16, 16, 16));  

            // Lo dispongo en el centro de la pantalla
            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .vel{0,0},.mov_speed =0, .size{float(mapMan.getTileSize().y),float(mapMan.getTileSize().x)}};

            // e.render->Sprite.move(
            //     e.physics->pos.x,
            //     e.physics->pos.y
            // );


            return e;
        }


        game::Entity::id_type GameManager::createEnemyArrive(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, double friction, double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(ENEMY_B);

            e.AI     = game::AIComponent        { .targetCoord{targetCoord}, .behaviour=FVAI::SB::PATHFINDING, .friction = friction, .time2arrive = 1 , .arrivalRadius = 2, .perceptionTime=perceptionTime}; //ÑÑÑÑ cambiar behaviour a arrive

            e.render  = game::RenderComponent   { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)}};

            e.reward = game::RewardComponent    {.min_reward = 1, .max_reward = 3};

            float life = 50;
            e.health = game::HealthComponent    { .maxLife = life, .currentLife = life, .inmortalityTime = 0};   

            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);


            e.render  = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)}};

            initEntityRender(e,{0,0},SFMLeng::SpriteManager::rect_i_type(0 * 62, 0 * 62, 62, 62));  

            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/8, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.coll = game::CollisionComponent{};      

            return e.id();     
        }
        
        std::vector<std::vector<int>>& GameManager::getMapGridRepresentation()
        {
            return mapMan.getMapGridRepresentation();
        }

        FVmath::Point2Di GameManager::worldPositionToGrid(float x, float y)
        {
            FVmath::Point2Di start        = {static_cast<int>(x), static_cast<int>(y)};
            FVmath::Point2Di gridPosition = {static_cast<int>(std::trunc(start.x / tileSize)), static_cast<int>(std::trunc(start.y / tileSize))};  // * applied scale??
            return gridPosition;
        }

        game::Entity::id_type GameManager::createEnemyShoot(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID, double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(ENEMY_A);           

            e.AI        = game::AIComponent         { .targetCoord{targetCoord}, .behaviour = FVAI::SB::SHOOTATTACK, .targetID=targetID, .perceptionTime=perceptionTime};         
                                    
            e.render    = game::RenderComponent     { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            e.reward    = game::RewardComponent     {.min_reward = 2, .max_reward = 4};

            float life = 50;
            e.health    = game::HealthComponent    { .maxLife = life, .currentLife = life, .inmortalityTime = 0}; 

            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);


            e.render->Sprite.setScale(0.2,0.2);

            initEntityRender(e,{0,0},SFMLeng::SpriteManager::rect_i_type(1 * 75, 2 * 75, 75, 75));
        
            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/8, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.coll = game::CollisionComponent{};  

            return e.id();
        }

        void GameManager::createBullet(FVmath::Point2Di Pos, FVmath::Point2Di Vel){

            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(BULLET_TEXT);
            std::cout <<  "NUM TEXTURA: " << texIdx << std::endl;

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{Pos.x,Pos.y}};

            initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(0 * 75, 0 * 75, 40, 40));

            e.physics = game::PhysicsComponent{ .pos{float(Pos.x)+30,float(Pos.y)+35}, .prevPos{float(Pos.x)+30,float(Pos.y)+35},  .vel{float(Vel.x),float(Vel.y)}, .mov_speed = 640/4, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.coll = game::CollisionComponent{};

            //Set player bullet
            e.addTag(game::Entity::TAG::Bullet);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);
            e.addTag(game::Entity::TAG::Player);
        }

        void GameManager::createEnemyBullet(FVmath::Point2D Pos, FVAI::SB sb, FVmath::Point2D targetCoord)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(BULLET_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{(int)Pos.x,(int)Pos.y}};

            initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(0 * 15, 0 * 15, 15, 15));

            e.physics = game::PhysicsComponent{ .pos{float(Pos.x)+30,float(Pos.y)+35}, .prevPos{float(Pos.x)+30,float(Pos.y)+35},  .vel{float(0),float(0)}, .mov_speed = 640/4, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };

            e.render->Sprite.setColor(sf::Color(200, 0, 0, 255));
            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );      

            e.AI     = game::AIComponent     { .targetCoord = targetCoord,.behaviour = sb, .arrivalRadius = 1 ,.maxTimeAlive = 4};

            e.AI->targetCoord = targetCoord;
            e.AI->behaviour   = sb;

            //Set player bullet
            e.addTag(game::Entity::TAG::Bullet);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);
            e.addTag(game::Entity::TAG::Enemy);
        }

        void GameManager::createPetBullet(FVmath::Point2D Pos, FVAI::SB sb, FVmath::Point2D targetCoord)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(BULLET_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{(int)Pos.x,(int)Pos.y}};

            initEntityRender(e, {0,0}, SFMLeng::SpriteManager::rect_i_type(0 * 15, 0 * 15, 15, 15));

            e.physics = game::PhysicsComponent{ .pos{float(Pos.x)+30,float(Pos.y)+35}, .prevPos{float(Pos.x)+30,float(Pos.y)+35},  .vel{float(0),float(0)}, .mov_speed = 640/4, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };

            e.render->Sprite.setColor(sf::Color(200, 0, 0, 255));
            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );      

            e.AI     = game::AIComponent     { .targetCoord = targetCoord,.behaviour = sb, .arrivalRadius = 10, .perceptionTime = 100, .maxTimeAlive = 1.25};

            e.AI->targetCoord = targetCoord;
            e.AI->behaviour   = sb;

            //Set player bullet
            e.addTag(game::Entity::TAG::Bullet);
            e.addTag(game::Entity::TAG::Player);

            
        }

        //Create all spawners on the current map
        void GameManager::createAllSpawner()
        {
            for(auto& spawner : mapMan.getSpawners())
                createSpawner(spawner,0);
            
        }

        //Create all doors on the current map
        void GameManager::createAllDoors()
        {
            for(auto& door : mapMan.getDoors())
                createDoor(door);
        }

        //Create all rooms on the current map
        void GameManager::createAllRooms()
        {
            for(auto& room : mapMan.getRooms())
                createRoom(room);
        }

        //Creates a concrete instance of a Spawner
        void GameManager::createSpawner(tXMLeng::Spawner& spawner,game::Entity::id_type id)
        {
            auto& e = EM_.createEntity();

            e.Spawn = game::SpawnerComponent{.SpawnInfo{spawner}, .ownerID = id};

            if(e.Spawn->SpawnInfo.type & tXMLeng::object_type::ENEMY)
                SpawnersID.push_back(e.id());
            else if(e.Spawn->SpawnInfo.type & tXMLeng::object_type::PLAYER)
            {
                e.Spawn->minTime=0;
            }

            e.addTag(game::Entity::TAG::SPAWNER);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);
            e.addTag(game::Entity::TAG::KILL_ON_ROOM_DELETE);  

        }

        void  GameManager::deleteKillable()
        {
            for(auto& ent :  EM_)
            {
                if(ent.hasTag(game::Entity::TAG::KILL_ON_MAP_CHANGE))
                {
                    ent.mark4destruction();
                }
            }
        }

        void GameManager::roomDelete(game::Entity::id_type room_id)
        {
            auto isRoom = [&](game::Entity& e){return e.hasTag(game::Entity::TAG::ROOM) && e.id()==room_id;};
            auto isRoomTrigger = [&](game::Entity& e){return e.hasTag(game::Entity::TAG::TRIGGER) && e.Spawn->ownerID==room_id;};
            auto isRoomBlockage = [&](game::Entity& e){return e.hasTag(game::Entity::TAG::STATIC_COLL) ;};
            auto isRoomSpawner = [&](game::Entity& e){return e.hasTag(game::Entity::TAG::SPAWNER) && e.Spawn->ownerID==room_id;};

            auto isRoomObject = [&](game::Entity& e){return (isRoom(e) || isRoomTrigger(e) || isRoomBlockage(e) || isRoomSpawner(e));};

            for(auto& ent : EM_)
            {
                if(ent.hasTag(game::Entity::TAG::KILL_ON_ROOM_DELETE) && isRoomObject(ent))
                {
                    ent.mark4destruction();
                }
            }
        }


        void GameManager::update()
        {
            if(change_level)
            {
                deleteKillable();
                LoadLevel();
            }
        }

        void GameManager::LoadLevel()
        {

            if(mapID_!=0) mapMan.clearMap();

            mapMan.InitMap(nextLevel.c_str());

            if(mapID_!=0) changeMap();
            else
            {
                SPman.loadTexture(mapMan.getTexturePath(), MAP_TEXT);
                createMap();
            } 

            createAllSpawner();
            createAllDoors();
            createAllRooms();


        }

        //Loads next layer info in the Sprite, to change layer being drawn
        void GameManager::setRenderNextLayer(game::MapComponent& map)
        {
            int currentLayer = mapMan.getActiveLayer();
            currentLayer++;
            mapMan.setActiveLayer(currentLayer);
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSize());
        }

        //Called to reset Sprite info once all map layers have been drawn
        void GameManager::resetMap(game::MapComponent& map)
        {
            mapMan.setActiveLayer(0);
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSize());
        }


        game::Entity::id_type GameManager::createEnemyPursue(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

           

            e.AI  = game::AIComponent{ .targetCoord{targetCoord}, .behaviour =FVAI::SB::PURSUE, .targetID=targetID, .perceptionTime=perceptionTime};         
                                    
            e.render  = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            e.reward = game::RewardComponent    {.min_reward = 2, .max_reward = 4};

            float life = 50;
            e.health = game::HealthComponent    { .maxLife = life, .currentLife = life, .inmortalityTime = 0}; 

            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);


            
            e.render  = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            initEntityRender(e,{0,0},SFMLeng::SpriteManager::rect_i_type(1 * 75, 0 * 75, 75, 75));

            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/8, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );    

            e.coll = game::CollisionComponent{};  

            return e.id();
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

            initEntityRender(e,{0,0},SFMLeng::SpriteManager::rect_i_type(row * 75, 1 * 75, 75, 75));

            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);

        }

        void GameManager::createHealth(FVmath::Point2D Pos)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(HEART_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{(int)Pos.x,(int)Pos.y}};

            initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(0,0,38,30));

            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .prevPos{float(Pos.x),float(Pos.y)},  .vel{}, .mov_speed = 0, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );      

            e.effct = game::EffectComponent{};

            e.effct->effects.push_back(effMan.createEffectNamed("Healing"));

            e.addTag(game::Entity::TAG::Health);
        }

        void GameManager::createDoor(tXMLeng::DoorInfo door)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(door.pos.x),int(door.pos.y)}};

            initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(2*mapMan.getTileSize().x,14*mapMan.getTileSize().y,door.size.x,door.size.y));

            e.physics = game::PhysicsComponent{ .pos{float(door.pos.x),float(door.pos.y)}, .prevPos{float(door.pos.x),float(door.pos.y)},  .vel{}, .mov_speed = 0, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );      

            e.map = game::MapComponent { .texIndex=-1, .FVSprite{}, .maxLowerLayer=-1, .object_type= game::map_object_t::DOOR, .nextLevel = door.next_level_path};

            e.coll = game::CollisionComponent{};

            e.addTag(game::Entity::TAG::DOOR);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);

        }

        void GameManager::createRoomTrigger(tXMLeng::room_trigger& trigger, game::Entity::id_type id)
        {
            auto& e = EM_.createEntity();

            e.physics = game::PhysicsComponent{ .pos{float(trigger.pos.x),float(trigger.pos.y)}, .prevPos{float(trigger.pos.x),float(trigger.pos.y)},  .vel{}, .mov_speed = 0, .size{float(trigger.size.x),float(trigger.size.y)} };   

            e.coll = game::CollisionComponent{};

            e.Spawn = game::SpawnerComponent{ .ownerID = id};

            e.addTag(game::Entity::TAG::TRIGGER);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);
            e.addTag(game::Entity::TAG::KILL_ON_ROOM_DELETE);  


        }

        void GameManager::createRoomBlockage(tXMLeng::room_blockage& block, game::Entity::id_type id)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(block.pos.x),int(block.pos.y)}};

            initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(4*mapMan.getTileSize().x,12*mapMan.getTileSize().y,block.size.x,block.size.y));

            e.physics = game::PhysicsComponent{ .pos{float(block.pos.x),float(block.pos.y)}, .prevPos{float(block.pos.x),float(block.pos.y)},  .vel{}, .mov_speed = 0, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );      

            e.coll = game::CollisionComponent{};

            e.addTag(game::Entity::TAG::STATIC_COLL);
            e.addTag(game::Entity::TAG::KILL_ON_MAP_CHANGE);
            e.addTag(game::Entity::TAG::KILL_ON_ROOM_DELETE);  

        }

        void GameManager::createRoom(tXMLeng::Room& room)
        {
            auto& e = EM_.createEntity();

            //CREATE ROOM TRIGGER SAVE IT ID
            createRoomTrigger(room.trigger,e.id());

            e.room = game::RoomComponent{ .roomInfo = room};

            e.addTag(game::Entity::TAG::ROOM); 
            e.addTag(game::Entity::TAG::KILL_ON_ROOM_DELETE);  

                     
        }

        void GameManager::instantiateRoom(tXMLeng::Room& room,game::Entity::id_type id)
        {
            //CREATE ROOM BLOCKS AND SAVE THEIR ID
            for(auto& block : room.blocks)
            {
                createRoomBlockage(block,id);
            }
            //CREATE SPAWNERS AND SAVE THEIR ID
            for(auto& spawn : room.spawners)
            {
                createSpawner(spawn,id);
            }
        }

        [[maybe_unused]] game::Entity&  GameManager::createHeart()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(HEART_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(0,0,38,30));

            return e;
        }

        [[maybe_unused]] game::Entity&  GameManager::createCoin()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(COIN_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(0,0,32,32));

            return e;
        }

        [[maybe_unused]] game::Entity&  GameManager::createClock()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(CLOCK_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(0,0,32,32));

            return e;
        }

        [[maybe_unused]] game::Entity&  GameManager::createShield()
        {
            auto& e     = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(SHIELD_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(0,0,32,32));

            return e;
        }

        void GameManager::initEntityRender(game::Entity& entity, FVmath::Point2D origin, SFMLeng::SpriteManager::rect_i_type TexRect)
        {
            //Y creo el spritesheet a partir de la imagen anterior
            SPman.assignTexture(entity.render->Sprite,entity.render->texIndex);
            //Le pongo el centroide donde corresponde
            SPman.modifySpriteOrigin(entity.render->Sprite, origin); //{0,0}
            //Cojo el sprite que me interesa por defecto del sheet
            SPman.modifyTextureRect(entity.render->Sprite, TexRect); //SFMLeng::SpriteManager::rect_i_type(0 * 75, 0 * 75, 75, 75));

        }

        void GameManager::setPlayerID(game::Entity::id_type id)
        {
            playerID_ = id;
        }


        game::Entity& GameManager::getPlayer()
        {
          return *EM_.getEntityByID(playerID_);
        }

}