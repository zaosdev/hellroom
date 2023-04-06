#include "GameManager.hpp"

namespace FVeng
{
        GameManager::GameManager(int x, int y, std::string nameGame)
        : window_(sf::VideoMode(x, y), nameGame)
        {
            window_.setKeyRepeatEnabled(true); // Habilitar entrada de teclado repetido
            window_.setFramerateLimit(60);
        }

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
        }

        void GameManager::initGame()
        {
            initLevel();
            LoadAllTextures();
            createMap();
            auto& player = createPlayer();
            bb_.targetID = player.id();

        }

        [[maybe_unused]] game::Entity& GameManager::createPlayer()
        {
            auto& e = EM_.createEntity();


            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);
            // Lo dispongo en el centro de la pantalla
            e.physics = game::PhysicsComponent{ .pos{320, 240}, .vel{0,0},.mov_speed =640/4};
            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(0 * 75, 0 * 75, 75, 75));

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.input = game::InputComponent{};

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

        void GameManager::createEnemyArrive(FVmath::Point2D Pos,FVmath::Point2D targetCoord, double friction, double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

            e.physics = game::PhysicsComponent{ .pos{Pos}, .vel{0,0}, .mov_speed =640/4};
            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(0 * 75, 0 * 75, 75, 75));

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.AI  = game::AIComponent      { .targetCoord{targetCoord}, .behaviour=FVAI::SB::ARRIVE, .friction = friction, .perceptionTime=perceptionTime}; 
                          
                                    
        }

        void GameManager::setRenderNextLayer(game::MapComponent& map)
        {
            int currentLayer = mapMan.getActiveLayer();
            currentLayer++;
            mapMan.setActiveLayer(currentLayer);
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSizePath());
        }

        void GameManager::resetMap(game::MapComponent& map)
        {
            mapMan.setActiveLayer(0);
            map.FVSprite.initVertexArray(mapMan.getMapSize(), mapMan.getCurrentLayer(), mapMan.getTileSizePath());
        }


        void GameManager::createEnemyPursue(FVmath::Point2D Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime)
        {
            auto& e = EM_.createEntity();

            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);

            e.physics = game::PhysicsComponent{ .pos{Pos}, .vel{0,0},.mov_speed =640/4};
            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{int(Pos.x),int(Pos.y)} };

            initEntityRender(e,{75 / 2, 75 / 2},sf::IntRect(0 * 75, 0 * 75, 75, 75));

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );               

            e.AI  = game::AIComponent      { .targetCoord{targetCoord}, .behaviour =FVAI::SB::PURSUE, .targetID=targetID, .perceptionTime=perceptionTime};         
                                    
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



}