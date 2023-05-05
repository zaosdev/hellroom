#include "collisionSys.hpp"
#include <iostream>

namespace game
{
  CollisionSys::CollisionSys(FVeng::GameManager& gameMan/*, SFMLeng::SpriteManager& spriteMan*/)
  : gMan_(gameMan)/*, spriteMan_(spriteMan)*/{


  }
  
  

  CollisionSys::~CollisionSys() = default;


  void CollisionSys::noOverlap(game::Entity& ent1, game::Entity& ent2){
    sf::Sprite& sprite1 = ent1.render->Sprite;
    sf::FloatRect ent1_bbox = sprite1.getGlobalBounds();
    sf::Sprite& sprite2 = ent2.render->Sprite;
    sf::FloatRect ent2_bbox = sprite2.getGlobalBounds();

    // Verificar si los dos objetos se superponen
    if (ent1_bbox.intersects(ent2_bbox)) {

      //std::cout << "COLISIONAN" << std::endl;
        // Obtener la distancia entre los dos objetos
        float distance = std::sqrt(std::pow(sprite1.getPosition().x - sprite2.getPosition().x, 2) +
                                   std::pow(sprite1.getPosition().y - sprite2.getPosition().y, 2));
        // Calcular la distancia necesaria para separar los dos objetos
        float overlap = (distance - ent1_bbox.width / 2 - ent2_bbox.width / 2) / 2;
        // Calcular la dirección en la que alejar cada objeto
        sf::Vector2f dir1 = sprite1.getPosition() - sprite2.getPosition();

        /*if(distance != 0)*/ dir1 /= distance;
        //else dir1.x = 72; dir1.y = 72;
        sf::Vector2f dir2 = -dir1;
        // Alejar los dos objetos en direcciones opuestas
        sf::Vector2f newposent1 = dir1 * overlap;
        sf::Vector2f newposent2 = dir2 * overlap;

        // Actualizar la posición de los objetos
        ent1.render->Sprite.setPosition(sprite1.getPosition() + newposent1);
        ent2.render->Sprite.setPosition(sprite2.getPosition() + newposent2);


        // std::cout << "DISTANCE " << distance << "\n" << " OVERLAP " << overlap << "\n" << " dir1.x " << dir1.x << " dir1.y " << dir1.y << "\n" << " dir2.x " << dir2.x << " dir2.y " << dir2.y << "\n" << " ENT 1 POS " << ent1.render->Sprite.getPosition().x << "\n" << " ENT 2 POS " << ent2.render->Sprite.getPosition().x << std::endl;

    }
}


    // void CollisionSys::colliding(){
      
    //   if(player_bbox.intersects(enemy_bbox)){ 
        
    //     //std::cout << "Player y Enemy estan colisionando restar vida a player" << std::endl;
    //     //if player and enemy colliding then call healthsys 
        
    //   }
    //   if(enemy_bbox.intersects(enemy_bbox)){
    //     //std::cout << "Colision entre enemigos" << std::endl;
    //    // noOverlap(enemy1_sprite, enemy2_sprite, enemy1_bbox, enemy2_bbox);
    //   }
    //   //faltaria colision con mapa y al tener armas colision con balas
    // }
     
    void CollisionSys::update()
    {
      
    //la idea es sacar del game la entidgame::Entity::TAG::Playerd usar el hasTag y con suerte obtener el bbox y asi comprobar colisiones con el intersect() y luego gestionarlas -> llamar a healthsys para que gestione temas de salud y crear una funcion que detenga el desplazamiento o permita empujar 
      auto& EM = gMan_.getEntityManager();
      
    
      sf::Sprite* playerSprite;
      std::vector<sf::Sprite*> enemySprites;

      //Entity and enemy obtention loop
      for(auto& ent : EM){
        if(ent.hasTag(game::Entity::TAG::Player))
        {
          playerSprite  = &ent.render->Sprite;
          player_bbox   = ent.render->Sprite.getGlobalBounds();
        }
       
        else if(ent.hasTag(game::Entity::TAG::Enemy))
        {
          enemySprites.push_back(&ent.render->Sprite);
          enemy_bbox = ent.render->Sprite.getGlobalBounds();
        }
      }

      //Acction loop. Every enemy against player
      for(auto& enemySprite : enemySprites)
      {
          //noOverlap(*playerSprite, *enemySprite); si vas a usar esto cambialo para qie acepte sprites
      }


          
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
