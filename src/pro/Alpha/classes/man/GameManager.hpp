#pragma once
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../cmp/blackBoardComponent.hpp"
#include "../utils/AI.hpp"
#include "../utils/random.hpp"
#include "../utils/gameData.hpp"


#include "entityManager.hpp"
#include "SpriteManager.hpp"
#include "mapManager.hpp"
#include "effectManager.hpp"




namespace FVeng
{
    struct GameManager
    {

        #define ENEMY_A     "enemyA_sprite"
        #define ENEMY_B     "enemyB_sprite"   

        static constexpr const char* PLAYER_TEXT = "player_sprite";
        static constexpr const char* MAP_TEXT    = "map_sprite";
        static constexpr const char* HEART_TEXT  = "heart_sprite";
        static constexpr const char* COIN_TEXT   = "coin_sprite";
        static constexpr const char* GUN_CRUZ_TEXT = "gun_cruz_sprite";
        static constexpr const char* GUN_ESCOPETA_TEXT = "gun_escopeta_sprite";
        static constexpr const char* GUN_RAFAGA_TEXT = "gun_rafaga_sprite";
        static constexpr const char* CLOCK_TEXT  = "clock_sprite";
        static constexpr const char* BULLET_TEXT = "bullet_sprite";
        static constexpr const char* COFRE_TEXT  = "chest_sprite";
        static constexpr const char* PET1_TEXT   = "pet1_sprite";
        static constexpr const char* PET2_TEXT   = "pet2_sprite";
        static constexpr const char* PET3_TEXT   = "pet3_sprite";
        static constexpr const char* SHIELD_TEXT = "shield_sprite";
        static constexpr const char* TRAP_TEXT   = "trap_sprite";

        GameManager(sf::RenderWindow& window);

        GameManager (const GameManager&) = delete;
        GameManager (GameManager&&) = delete;
        GameManager& operator=(const GameManager&)= delete;
        GameManager& operator=(GameManager&&)= delete;       
        
        sf::RenderWindow& getWindow();
        void initLevel();
        void initGame();
        game::Entity& createPlayer(FVmath::Point2Di Pos);
        game::Entity& createPet   (FVmath::Point2Di Pos);
        game::Entity& createHeart   ();
        game::Entity& createCoin    ();
        game::Entity& createClock   ();
        game::Entity& createShield  ();
        game::Entity& createMapCollider(FVmath::Point2Di Pos);
        game::Entity& createGunCruz();
        game::Entity& createGunEscopeta();
        game::Entity& createGunRafaga();

        game::Entity::id_type createEnemyArrive(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, double friction,  double perceptionTime);
        game::Entity::id_type createEnemyPursue(FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime);
        game::Entity::id_type createEnemyShoot (FVmath::Point2Di Pos,FVmath::Point2D targetCoord, game::Entity::id_type targetID,  double perceptionTime);
        void createMap();
        void changeMap();
        void createHealth(FVmath::Point2D Pos);
        void createTrap(FVmath::Point2Di Pos);
        void createDoor(tXMLeng::DoorInfo door);
        void createCofre(FVmath::Point2Di Pos, int id);
        void createRoom(tXMLeng::Room& room);
        void instantiateRoom(tXMLeng::Room& room,game::Entity::id_type id);




        void createBullet(FVmath::Point2Di Pos, FVmath::Point2Di Vel);
        void createEnemyBullet(FVmath::Point2D Pos, FVAI::SB sb, FVmath::Point2D targetCoord);
        void createPetBullet(FVmath::Point2D Pos, FVAI::SB sb, FVmath::Point2D targetCoord);

        void createAllSpawner();
        void createAllDoors();
        void createAllTraps();
        void createAllRooms();


        void createRoomTrigger(tXMLeng::room_trigger& room, game::Entity::id_type id);
        void createRoomBlockage(tXMLeng::room_blockage& room, game::Entity::id_type id);
        void createSpawner(tXMLeng::Spawner& spawner , game::Entity::id_type id);


        void setPlayerID(game::Entity::id_type id);
        void setRenderNextLayer(game::MapComponent& map);
        void resetMap(game::MapComponent& map);
        void LoadAllTextures();
        void LoadLevel();
        void initEntityRender(game::Entity& entity, FVmath::Point2D origin, SFMLeng::SpriteManager::rect_i_type rect);
        void SpawnDummy(FVmath::Point2Di Pos);
        void deleteKillable();
        void roomDelete(game::Entity::id_type);
        std::vector<std::vector<int>>& getMapGridRepresentation();
        FVmath::Point2Di worldPositionToGrid(float x, float y);

        void update();

        FVeng::EntityManager<game::Entity>& getEntityManager();
        game::blackBoardComponent& getBB();
        tXMLeng::mapManager& getMapManager();
        game::Entity& getPlayer();
        
        std::vector<game::Entity::id_type> SpawnersID{}; 
        bool change_level{false};
        std::string nextLevel{"../media/level1.tmx"};


        private:
        SFMLeng::SpriteManager SPman{100};

        sf::RenderWindow& window_;
        //create Sprite manager
        tXMLeng::mapManager mapMan{};
        FV_factory::effectsFactory effMan{};

        FVeng::EntityManager<game::Entity> EM_{500};
        game::blackBoardComponent bb_{} ;
        // bool allSpawned{false};
        game::Entity::id_type mapID_{0};
        game::Entity::id_type playerID_{0};

           
    };
}