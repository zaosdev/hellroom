#include "collisionSys.hpp"
#include "../classes/man/mapManager.hpp"
#include <iostream>

#define defaultDamage 30

namespace game
{
  CollisionSys::CollisionSys(FVeng::GameManager& gameMan/*, SFMLeng::SpriteManager& spriteMan*/)
  : gMan_(gameMan)/*, spriteMan_(spriteMan)*/{


  }
  
  

  CollisionSys::~CollisionSys() = default;

  //########################################################################

   void CollisionSys::noOverlap(Entity& ent1, Entity& ent2){

    sf::Sprite sprite1 = ent1.render->Sprite;
    sf::Sprite sprite2 = ent2.render->Sprite;

    sf::FloatRect sprite1Bbox = sprite1.getGlobalBounds();
    sf::FloatRect sprite2Bbox = sprite2.getGlobalBounds();

    sf::Vector2f sprite1POS = sprite1.getPosition();
    sf::Vector2f sprite2POS = sprite2.getPosition();

    FVmath::Point2D ent1POS = ent1.physics->pos;
    FVmath::Point2D ent2POS = ent2.physics->pos;


    sf::Vector2f s1_HalfSize = {sprite1Bbox.height /2.0f , sprite1Bbox.width / 2.0f};
    sf::Vector2f s2_HalfSize = {sprite2Bbox.height /2.0f , sprite2Bbox.width / 2.0f};

    float deltaX = sprite2POS.x - sprite1POS.x;
    float deltaY = sprite2POS.y - sprite1POS.y;

    // float deltaX = ent2POS.x - ent1POS.x;
    // float deltaY = ent2POS.y - ent1POS.y;

    float intersectX = std::abs(deltaX) - (s2_HalfSize.x + s1_HalfSize.x);
    float intersectY = std::abs(deltaY) - (s2_HalfSize.y + s1_HalfSize.y);

    playerCollision(intersectX, intersectY, deltaX, deltaY, ent2, ent2POS);
    //shieldCollision(intersectX, intersectY, deltaX, deltaY, ent1, ent2POS, ent2, ent2POS);
    
  }


  void CollisionSys::playerCollision(float intersectX, float intersectY,  float deltaX,  float deltaY, Entity& ent2, FVmath::Point2D ent2POS ){
    
    if(intersectX > intersectY) {

      if(deltaX > 0.0f){
        // ent1.physics->pos.x = ent1POS.x + (intersectX * (1.0f /*- push*/));
        
        //ent2.physics->mov_speed = 0.0f;
        ent2.physics->pos.x = ent2POS.x + (-intersectX);
        
      }
      else{
        // ent1.physics->pos.x = ent1POS.x +  (-intersectX * (1.0f /*- push*/));
        //ent2.physics->mov_speed = 0.0f;
        ent2.physics->pos.x = ent2POS.x +  (intersectX );
        
      }
    }
    else{
      if(deltaY > 0.0f){
      //ent1.physics->pos.y = ent1POS.y + (intersectY * (1.0f /*- push*/));
        //ent2.physics->mov_speed = 0.0f;

        ent2.physics->pos.y = ent2POS.y + (-intersectY);
          
      }

      else{

        // ent1.physics->pos.y = ent1POS.y + (-intersectY * (1.0f /*- push*/));
  
        //ent2.physics->mov_speed = 0.0f;
        
        ent2.physics->pos.y = ent2POS.y + (intersectY);

      }
    }
  }

  //void CollisionSys::shieldCollision(float intersectX, float intersectY,  float deltaX,  float deltaY, Entity& ent1, FVmath::Point2D ent1POS, Entity& ent2, FVmath::Point2D ent2POS ){
    
    // std::cout << " SHIELD " << std::endl;
    
    // if(intersectX > intersectY) {

    //   if(deltaX > 0.0f){
    //     //ent1.physics->pos.x = ent1POS.x + (intersectX * (1.0f /*- push*/));
        
    //     ent2.physics->pos.x = ent2POS.x + (-intersectX);
        
    //   }
    //   else{
    //     //ent1.physics->pos.x = ent1POS.x +  (-intersectX * (1.0f /*- push*/));
        
    //     ent2.physics->pos.x = ent2POS.x +  (intersectX );
   
        
    //   }
    // }
    // else{
    //   if(deltaY > 0.0f){
    //     //ent1.physics->pos.y = ent1POS.y + (intersectY * (1.0f /*- push*/));
        
    //     ent2.physics->pos.y = ent2POS.y + (-intersectY);
       

    //   }

    //   else{

    //     //ent1.physics->pos.y = ent1POS.y + (-intersectY * (1.0f /*- push*/)); 
        
    //     ent2.physics->pos.y = ent2POS.y + (intersectY);

       

    //   }
    // }
  //}

     
    void CollisionSys::update()
    {
      
    //la idea es sacar del game la entidgame::Entity::TAG::Playerd usar el hasTag y con suerte obtener el bbox y asi comprobar colisiones con el intersect() y luego gestionarlas -> llamar a healthsys para que gestione temas de salud y crear una funcion que detenga el desplazamiento o permita empujar 
      auto& EM = gMan_.getEntityManager();
      
    
      sf::Sprite* playerSprite;
      //std::vector<sf::Sprite*> enemySprites;
      std::vector<Entity*> enemies;
      std::vector<Entity*> enemyBullets;
      Entity* player;
      std::vector<Entity*> playerBullets;

      //Entity and enemy obtention loop
      for(auto& ent : EM){
        if(ent.hasTag(game::Entity::TAG::Player))
        {
          if(ent.hasTag(game::Entity::TAG::Bullet))
          {
            playerBullets.push_back(&ent);
          }
          else
          {
            player = &ent;
            playerSprite  = &ent.render->Sprite;
            playerBbox   = ent.render->Sprite.getGlobalBounds();
          }
        }
       
        else if(ent.hasTag(game::Entity::TAG::Enemy))
        {
          
          //enemy bullet
          if(ent.hasTag(game::Entity::TAG::Bullet))
          {
            enemyBullets.push_back(&ent);
          }
          else
          {
            enemies.push_back(&ent);
          }
        }
      }



      //Action loops - ENEMY - PLAYER
      for(auto& enemyEnt : enemies)
      {
        if(playerBbox.intersects(enemyEnt->render->Sprite.getGlobalBounds()))
        {
          noOverlap(*player, *enemyEnt);
          player->health->negativeAffection = defaultDamage / 2;
        }
      }

      //Action loops - PLAYER BULLETS - ENEMIES
      for(auto& playerBullet : playerBullets)
      {
        for(auto& enemy : enemies)
        {
          auto bulletBB = playerBullet->render->Sprite.getGlobalBounds();
          auto enemyBB  = enemy->render->Sprite.getGlobalBounds();
          if(bulletBB.intersects(enemyBB))
          {
            noOverlap(*playerBullet, *enemy);
            playerBullet->mark4destruction();
            enemy->health->negativeAffection = defaultDamage;
          }
        }
      }
        
    }


      //Acction loop. Every enemy against player
      // for(auto& enemySprite : enemySprites)
      // {
        
      //   if (playerBbox.intersects(enemySprite->getGlobalBounds())){  entidad->physics->pos.x = 0; entidad->physics->pos.y = 0; }
 
      //   //std::cout << "ENEMY  " << enemySprites.size() << std::endl;
      //   //noOverlap(*playerSprite, *enemySprite); //si vas a usar esto cambialo para que acepte sprites
      // }


          
          // }
    //}

        // if(player_bbox.intersects(enemy_bbox)){ 


        //    // std::cout << "COLISIONAN" << std::endl;

        //   // // Calcular la dirección en la que mover los sprites
        //   // float offsetX = std::abs(player_sprite.getPosition().x - enemy_sprite.getPosition().x);
        //   // float offsetY = std::abs(player_sprite.getPosition().y - enemy_sprite.getPosition().y);
        //   // sf::Vector2f offset;
        //   // if (offsetX > offsetY) {
        //   //     offset.x = player_sprite.getPosition().x > enemy_sprite.getPosition().x ? offsetX : -offsetX;
        //   // } else {
        //   //     offset.y = player_sprite.getPosition().y > enemy_sprite.getPosition().y ? offsetY : -offsetY;
        //   // }

        //   // // Reposicionar los sprites para que no se solapen
        //   // player_sprite.move(offset / 2.f);
        //   // enemy_sprite.move(-offset / 2.f);
        
        // //  //std::cout << "Player y Enemy estan colisionando restar vida a player" << player_bbox.intersects(enemy_bbox) << std::endl;
        // // //if player and enemy colliding then call healthsys
          
        //     //std::cout << "COLISIONAN" << std::endl;
        //       // Obtener la distancia entre los dos objetos
        //       float distance = std::sqrt(std::pow(player_sprite.getPosition().x - enemy_sprite.getPosition().x, 2) +
        //                                 std::pow(player_sprite.getPosition().y - enemy_sprite.getPosition().y, 2));
        //       // Calcular la distancia necesaria para separar los dos objetos
        //       float overlap = (distance - player_bbox.width / 2 - enemy_bbox.width / 2) / 2;
        //       // Calcular la dirección en la que alejar cada objeto
        //       sf::Vector2f dir1 = player_sprite.getPosition() - enemy_sprite.getPosition();
        //       dir1 /= distance;
        //       sf::Vector2f dir2 = -dir1;
        //       // Alejar los dos objetos en direcciones opuestas
        //       sf::Vector2f newposplayer = dir1 * overlap;
        //       sf::Vector2f newposenemy = dir2 * overlap;


        //       //otra opcion  de momento ignorar
        //       // player_sprite.setPosition(player_sprite.getPosition() + correction);
        //       // enemy_sprite.setPosition(enemy_sprite.getPosition() - correction);
             

        //       // Actualizar la posición de los objetos
        //       //std::cout << " POS PREVIA   " << player_sprite.getPosition().x << std::endl;  

        //        player_sprite.setPosition(newposplayer);
        //        enemy_sprite.setPosition(newposenemy);


        //       // std::cout << "DISTANCE " << distance << "\n" << " OVERLAP " << overlap << "\n" << " r1.x " << dir1.x << " r1.y " << dir1.y << "\n" << " r2.x " << dir2.x << " r2.y " << dir2.y << "\n" << " PLAYER POS " << player_sprite.getPosition().x << "\n" << " ENEMY POS " << enemy_sprite.getPosition().x << std::endl;
              
        //   }
        //   else{
        //     //std::cout << "NO HAY COLISIONES" << std::endl;
        //   }
        
      //   }
        
      // }













      // std::cout << "BBOX PLAYER WIDTH:  " << player_bbox.width << "\n" << "BBOX PLAYER HEIGHT:  " << player_bbox.height << std::endl;

      // std::cout << "BBOX ENEMY WIDTH:  " << enemy_bbox.width << "\n" << "BBOX ENEMY HEIGHT:  " << enemy_bbox.height << std::endl;

    }
