#include "collisionSys.hpp"
#include <iostream>

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


    if(intersectX > intersectY) {

      if(deltaX > 0.0f){
        // ent1.physics->pos.x = ent1POS.x + (intersectX * (1.0f /*- push*/));

        ent2.physics->pos.x = ent2POS.x + (-intersectX);
        
      }
      else{
        // ent1.physics->pos.x = ent1POS.x +  (-intersectX * (1.0f /*- push*/));

        ent2.physics->pos.x = ent2POS.x +  (intersectX );
        
      }
    }
    else{
      if(deltaY > 0.0f){
      //ent1.physics->pos.y = ent1POS.y + (intersectY * (1.0f /*- push*/));
 
        ent2.physics->pos.y = ent2POS.y + (-intersectY);
          
      }

      else{

        // ent1.physics->pos.y = ent1POS.y + (-intersectY * (1.0f /*- push*/));
  

        ent2.physics->pos.y = ent2POS.y + (intersectY);

      }
    }

 // #####################################################################################################



  //   //OTRA IDEA


  //   //  // Calcular la dirección en la que mover los sprites
  //   //       float offsetX = std::abs(sprite2POS.x - sprite1POS.x);
  //   //       float offsetY = std::abs(sprite2POS.y - sprite1POS.y);
  //   //       sf::Vector2f offset;
  //   //       if (offsetX > offsetY) {
  //   //           offset.x = sprite2POS.x  > sprite1POS.x  ? offsetX : -offsetX;
                            

  //   //       } else {
  //   //           offset.y = sprite2POS.y > sprite1POS.y ? offsetY : -offsetY;
  //   //       }

  //   //       // Reposicionar los sprites para que no se solapen
  //   //       ent1.physics->pos.x = ent1POS.x ;
  //   //       ent1.physics->pos.y = ent1POS.y ;
  //   //       ent2.physics->pos.x = ent2POS.x + (-offset.x / 2.f);
  //   //       ent2.physics->pos.y = ent2POS.y + (-offset.y / 2.f);


  //  /////PROBEMOS OTRA IDEA 

  // // //void CollisionSys::noOverlap(sf::Sprite& sprite1, sf::Sprite& sprite2){
  // //   sf::Sprite sprite1 = ent1.render->Sprite;
  // //   sf::Sprite sprite2 = ent2.render->Sprite;

    
  // //   sf::FloatRect sprite1Bbox = sprite1.getGlobalBounds();
  // //   sf::FloatRect sprite2Bbox = sprite2.getGlobalBounds();

  // //   // std::cout << " Player BBOX  " << sprite1Bbox.width << std::endl;
  // //   // std::cout << " Enemy BBOX  " << sprite2Bbox.width << std::endl;


  //   // // Verificar si los dos objetos se superponen
  //   // if (sprite1Bbox.intersects(sprite2Bbox)) {

  //     /////PONGO EN PAUSA ESTA IDEA, VOY A PROBAR OTRA

  //     // //std::cout << "COLISIONAN" << std::endl;
  //     //   // Obtener la distancia entre los dos objetos
  //     //   float distance = std::sqrt(std::pow(sprite1.getPosition().x - sprite2.getPosition().x, 2) +
  //     //                              std::pow(sprite1.getPosition().y - sprite2.getPosition().y, 2));
  //     //   // Calcular la distancia necesaria para separar los dos objetos
  //     //   float overlap = (distance - sprite1Bbox.width / 2 - sprite2Bbox.width / 2) / 2;
  //     //   // Calcular la dirección en la que alejar cada objeto
  //     //   sf::Vector2f dir1 = sprite1.getPosition() - sprite2.getPosition();

  //     //   if(distance != 0) dir1 /= distance;
  //     //   else dir1.x = 1.0f; dir1.y = 1.0f;

  //     //   sf::Vector2f dir2 = -dir1;
  //     //   // Alejar los dos objetos en direcciones opuestas
  //     //   sf::Vector2f newpossprite1 = dir1 * overlap;
  //     //   sf::Vector2f newpossprite2 = dir2 * overlap;


  //     //   // const float dampingFactor = 0.9f;

  //     //   // newpossprite1 *= dampingFactor;
  //     //   // newpossprite2 *= dampingFactor;

  //     //   FVmath::Point2D newpos1;
  //     //   newpos1.x = newpossprite1.x;
  //     //   newpos1.y = newpossprite1.y;

  //     //   FVmath::Point2D newpos2;
  //     //   newpos2.x = newpossprite2.x;
  //     //   newpos2.y = newpossprite2.y;

        

  //     //   //FVmath::Point2D newpos2(newpossprite2.x, newpossprite2.y);

  //     //   // Actualizar la posición de los objetos

  //     //   // sprite1.move(newpossprite1);
  //     //   // sprite2.move(newpossprite2);

  //     //  // ent1.physics->pos += newpos1;    /*+= ent.physics->vel * dt*/
  //     //   ent2.physics->pos += newpos2;

  //     //   // sprite1.setPosition(newpossprite1);
  //     //   // sprite2.setPosition(newpossprite2);

  //     //   //std::cout << " ent1 X " << ent1.physics->pos.x << std::endl;
  //     //   //std::cout << " ent2 X " << ent2.physics->pos.x << std::endl;

  //     //   //sigue sin verse la colision pero lo calcula bien, no veo donde esta el problema

  //     //   // std::cout << "DISTANCE " << distance << "\n" << " OVERLAP " << overlap << "\n" << " dir1.x " << dir1.x << " dir1.y " << dir1.y << "\n" << " dir2.x " << dir2.x << " dir2.y " << dir2.y << "\n" << " ENT 1 POS " << sprite1.getPosition().x << "\n" << " ENT 2 POS " << sprite2.getPosition().x << std::endl;

     }

  /*
  ############################################################################################
  //VERSION MAS LIMPIA DE noOverlap

    void CollisionSys::noOverlap(Entity& ent1, Entity& ent2) {
      sf::Sprite& sprite1 = ent1.render->Sprite;
      sf::Sprite& sprite2 = ent2.render->Sprite;

      sf::Vector2f sprite1POS = sprite1.getPosition();
      sf::Vector2f sprite2POS = sprite2.getPosition();

      sf::FloatRect sprite1Bbox = sprite1.getGlobalBounds();
      sf::FloatRect sprite2Bbox = sprite2.getGlobalBounds();

      float intersectX = std::abs(sprite2POS.x - sprite1POS.x) - (sprite2Bbox.width / 2.0f + sprite1Bbox.width / 2.0f);
      float intersectY = std::abs(sprite2POS.y - sprite1POS.y) - (sprite2Bbox.height / 2.0f + sprite1Bbox.height / 2.0f);

      if (intersectX > intersectY) {
        if (sprite2POS.x > sprite1POS.x) {
          ent2.physics->pos.x = sprite1POS.x + sprite1Bbox.width / 2.0f + sprite2Bbox.width / 2.0f;
        } else {
          ent2.physics->pos.x = sprite1POS.x - sprite1Bbox.width / 2.0f - sprite2Bbox.width / 2.0f;
        }
      } else {
        if (sprite2POS.y > sprite1POS.y) {
          ent2.physics->pos.y = sprite1POS.y + sprite1Bbox.height / 2.0f + sprite2Bbox.height / 2.0f;
        } else {
          ent2.physics->pos.y = sprite1POS.y - sprite1Bbox.height / 2.0f - sprite2Bbox.height / 2.0f;
        }
      }
    }
    ##################################################################################################
*/
     
    void CollisionSys::update(){
      
    //la idea es sacar del game la entidgame::Entity::TAG::Playerd usar el hasTag y con suerte obtener el bbox y asi comprobar colisiones con el intersect() y luego gestionarlas -> llamar a healthsys para que gestione temas de salud y crear una funcion que detenga el desplazamiento o permita empujar 
      auto& EM = gMan_.getEntityManager();
      
    
      sf::Sprite* playerSprite;
      //std::vector<sf::Sprite*> enemySprites;
      std::vector<Entity*> enemies;
      Entity* player;
      

      //Entity and enemy obtention loop
      for(auto& ent : EM){
        if(ent.hasTag(game::Entity::TAG::Player))
        {
          player = &ent;
          playerSprite  = &ent.render->Sprite;
          playerBbox   = ent.render->Sprite.getGlobalBounds();
        }
       
        else if(ent.hasTag(game::Entity::TAG::Enemy))
        {
          
          //entidad = &ent;
          enemies.push_back(&ent);
          //enemySprites.push_back(&ent.render->Sprite); 
          //enemyBbox = ent.render->Sprite.getGlobalBounds();
        }
      }

      for(auto& enemyEnt : enemies){
        
        if(playerBbox.intersects(enemyEnt->render->Sprite.getGlobalBounds())){
          noOverlap(*player, *enemyEnt);
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
    }

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
