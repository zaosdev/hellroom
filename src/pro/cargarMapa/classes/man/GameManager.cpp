#include "GameManager.hpp"

namespace FVeng
{
        GameManager::GameManager(int x, int y, std::string nameGame)
        : window_(sf::VideoMode(x, y), nameGame)
        {
            window_.setKeyRepeatEnabled(true); // Habilitar entrada de teclado repetido
            window_.setFramerateLimit(60);
        }

        sf::RenderWindow& GameManager::getWindow()
        {
            return window_;
        }

        FVeng::EntityManager<game::Entity>& GameManager::getEntityManager()
        {
            return EM_;
        }

        void GameManager::initLevel()
        {
            mapMan.InitMap("../media/Mapa1.tmx");
        }

        void GameManager::LoadAllTextures()
        {
            SPman.loadTexture("../resources/sprites.png", PLAYER_TEXT);
            SPman.loadTexture(mapMan.getTexturePath(), MAP_TEXT);


            // SPman.loadTexture(GameMan.ent->render->tex,"../resources/sprites.png");

        }

        void GameManager::initGame()
        {

        }
        void GameManager::createPlayer()
        {
            auto& e = EM_.createEntity();


            auto texIdx = SPman.getTextureIdxByName(PLAYER_TEXT);
            // Lo dispongo en el centro de la pantalla
            e.physics = game::PhysicsComponent{ .pos{320, 240}, .vel{0,0}};
            e.render = game::RenderComponent { .texIndex=texIdx  , .Sprite{}, .window_Pos{320,240} };

            e.render->Sprite.move(
                e.physics->pos.x,
                e.physics->pos.y
            );

            e.input = game::InputComponent{};
        }
        void GameManager::createMap()
        {

        }

        void GameManager::initEntityRender(game::Entity& entity, FVmath::vec2D origin, sf::IntRect TexRect)
        {
            //Y creo el spritesheet a partir de la imagen anterior
            SPman.assignTexture(entity.render->Sprite,entity.render->texIndex);
            //Le pongo el centroide donde corresponde
            SPman.modifySpriteOrigin(entity.render->Sprite, origin); //{75 / 2, 75 / 2}
            //Cojo el sprite que me interesa por defecto del sheet
            SPman.modifyTextureRect(entity.render->Sprite, TexRect); //sf::IntRect(0 * 75, 0 * 75, 75, 75));
        }



}