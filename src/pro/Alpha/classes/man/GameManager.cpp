#include "GameManager.hpp"

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

            SPman.loadTexture("../resources/sprites.png", PLAYER_TEXT);
            SPman.loadTexture(mapMan.getTexturePath(), MAP_TEXT);
            SPman.loadTexture("../media/HUD/heart-red.png", HEART_TEXT);
        }

        void GameManager::initGame()
        {
            initLevel();
            LoadAllTextures();
            createMap();
            createAllSpawner();
            auto& player = createPlayer({320,240});
            bb_.targetID = player.id();

        }

        [[maybe_unused]] game::Entity& GameManager::createPlayer(FVmath::Point2Di Pos)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);
            // Lo dispongo en el centro de la pantalla


            e.input  = game::InputComponent{};

            //health status 
            float life = 500;
            e.health = game::HealthComponent{ .maxLife = life, .currentLife = life, .inmortalityTime = 1 / 2};

            //add tag player
            e.addTag(game::Entity::TAG::Player); 

            //create life 

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0}, sf::IntRect(0 * 75, 0 * 75, 75, 75));

            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .vel{0,0},.mov_speed =640/4, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width}};

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.coll = game::CollisionComponent{};

            return e;
        }

        void GameManager::createMap()
        {
            auto& e = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(MAP_TEXT);
            e.map = game::MapComponent { .texIndex=texIdx, .FVSprite{}, .maxLowerLayer=mapMan.getMaxBaseLayer(), .mapCollider{false} };

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

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

            e.map = game::MapComponent { .texIndex=-1, .FVSprite{}, .maxLowerLayer=-1, .mapCollider=true };

            e.coll = game::CollisionComponent{};           

            e.addTag(game::Entity::TAG::STATIC_COLL);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            // Lo dispongo en el centro de la pantalla
            e.physics = game::PhysicsComponent{ .pos{float(Pos.x),float(Pos.y)}, .vel{0,0},.mov_speed =0, .size{float(mapMan.getTileSize().y),float(mapMan.getTileSize().x)}};
            
            initEntityRender(e, {0,0}, sf::IntRect(0 * e.physics->size.x, 0 * e.physics->size.y, e.physics->size.x, e.physics->size.y));

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            return e;
        }


        void GameManager::createEnemyArrive(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, double friction, double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

            e.AI     = game::AIComponent      { .targetCoord{targetCoord}, .behaviour=FVAI::SB::ARRIVE, .friction = friction, .time2arrive = 1 , .arrivalRadius = 2, .perceptionTime=perceptionTime}; 

            //health status 
            float life = 50;
            e.health = game::HealthComponent{ .maxLife = life, .currentLife = life, .inmortalityTime = 1 / 2};     

            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy); 

            e.render  = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)}};

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(1 * 75, 1 * 75, 75, 75));  

            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/4, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.coll = game::CollisionComponent{};           
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
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSize());
        }

        //Called to reset Sprite info once all map layers have been drawn
        void GameManager::resetMap(game::MapComponent& map)
        {
            mapMan.setActiveLayer(0);
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSize());
        }


        void GameManager::createEnemyPursue(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

           

            e.AI  = game::AIComponent      { .targetCoord{targetCoord}, .behaviour =FVAI::SB::PURSUE, .targetID=targetID, .perceptionTime=perceptionTime};         
                                    
            //add tag enemy
            e.addTag(game::Entity::TAG::Enemy); 

            
            e.render  = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(1 * 75, 0 * 75, 75, 75));

            FVmath::Point2D position = {float(Pos.x),float(Pos.y)};
            e.physics = game::PhysicsComponent{ .pos{position}, .prevPos{position}, .vel{0,0}, .mov_speed = 640/4, .size{e.render->Sprite.getGlobalBounds().height,e.render->Sprite.getGlobalBounds().width} };


            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );    

            e.coll = game::CollisionComponent{};  
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

            auto row = FVmath::calcualteRandom(3,1);

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(row * 75, 1 * 75, 75, 75));


        }

        [[maybe_unused]] game::Entity&  GameManager::createHeart()
        {
            auto& e = EM_.createEntity();
            auto texIdx = SPman.getTextureIdxByName(HEART_TEXT);

            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e, {0,0},sf::IntRect(0,0,38,30));

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