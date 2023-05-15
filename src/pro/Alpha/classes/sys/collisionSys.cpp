#include "collisionSys.hpp"
#include "../classes/man/mapManager.hpp"
#include <iostream>

namespace game
{
  CollisionSys::CollisionSys(FVeng::GameManager& gameMan/*, SFMLeng::SpriteManager& spriteMan*/)
  : gMan_(gameMan)/*, spriteMan_(spriteMan)*/{


  }  

  CollisionSys::~CollisionSys() = default;

  //########################################################################

    void CollisionSys::update(float dt)
    {
      //la idea es sacar del game la entidgame::Entity::TAG::Playerd usar el hasTag y con suerte obtener el bbox y asi comprobar colisiones con el intersect() y luego gestionarlas -> llamar a healthsys para que gestione temas de salud y crear una funcion que detenga el desplazamiento o permita empujar 
      auto& EM = gMan_.getEntityManager();
      
      //sf::Sprite* playerSprite{};
      //std::vector<sf::Sprite*> enemySprites;
      std::vector<Entity*> enemies{};
      std::vector<Entity*> stat_coll{};

      //bool nomore{false};

      Entity& player = gMan_.getPlayer();
      std::vector<std::pair<Entity*, float>> collInstance{};


      //Entity and enemy obtention loop
      for(auto& ent : EM)
      {
        if(!ent.hasTag(game::Entity::TAG::Player))
        {
          if(ent.hasTag(game::Entity::TAG::Enemy))
          {
            enemies.push_back(&ent);
            if (DynamicEntityVsStaticEntity(player, dt, ent))
            {
              collInstance.push_back({ &ent, player.coll->contactTime });
            }
          }
          else 
          if(ent.hasTag(game::Entity::TAG::STATIC_COLL))
          {
            stat_coll.push_back(&ent);
            		// Work out collision point, add it to vector along with rect ID
              // if(checkCollision(player,ent))
              // {
                if (DynamicEntityVsStaticEntity(player, dt, ent))
                {
                  collInstance.push_back({ &ent, player.coll->contactTime });
                }
              // }
          }
          //AÑADIR ELSE IF SI HAY MAS TIPOS DE COLISIONES
          // else if()
          // {

          // }
        }
      }

//////////////////////////////////
    if(!collInstance.empty())
    {
      // Do the sort
      std::sort(collInstance.begin(), collInstance.end(), [](const std::pair<Entity*, float>& a, const std::pair<Entity*, float>& b)
        {
          return a.second < b.second;
        });

      for (auto j : collInstance)
      {
        ResolveDynamicEntityVsEntity(player,*j.first,dt);
      }
    }
    player.physics->pos+=player.physics->vel*dt;
    // collInstance.clear();

      for(auto* enemy : enemies)
      {
        for(auto* wallColl : stat_coll)
        {
          if (DynamicEntityVsStaticEntity(*enemy, dt, *wallColl))
          {
            collInstance.push_back({wallColl, enemy->coll->contactTime });
          }
        }
        if (DynamicEntityVsStaticEntity(*enemy, dt, player))
        {
          collInstance.push_back({&player, enemy->coll->contactTime });
        }
        if(!collInstance.empty())
        {
          // Do the sort
          std::sort(collInstance.begin(), collInstance.end(), [](const std::pair<Entity*, float>& a, const std::pair<Entity*, float>& b)
            {
              return a.second < b.second;
            });

          for (auto j : collInstance)
          {
            ResolveDynamicEntityVsEntity(*enemy,*j.first,dt);
          }
        }
        collInstance.clear();
        enemy->physics->pos+=enemy->physics->vel*dt;
      }
    }

    bool CollisionSys::checkCollision(Entity& collider1, Entity& collider2)
    {
      auto rect1Pos = collider1.physics->pos;
      auto rect2Pos = collider2.physics->pos;

      auto rect1BBox = collider1.physics->size;
      auto rect2BBox = collider2.physics->size;

      // Expand target rectangle by source dimensions
      expandedTarget expanded_target{};
      expanded_target.pos = collider2.physics->pos - collider1.physics->size / 2;
      expanded_target.size = collider2.physics->size + collider1.physics->size;

      if (
        rect1Pos.x <= expanded_target.pos.x + expanded_target.size.x &&
        rect1Pos.x + rect1BBox.x >= expanded_target.pos.x &&
        rect1Pos.y <= expanded_target.pos.y + expanded_target.size.y &&
        rect1BBox.y + rect1Pos.y >= expanded_target.pos.y
      )
			{
          return true;
      }
			else
      {
          return false;
      }
  }

  bool CollisionSys::rayVsEntity(const FVmath::Point2D rayOrigin, const FVmath::Point2D rayDirection, expandedTarget& target,Entity& dynamicEntity)
  {
		dynamicEntity.coll->contactPoint = { 0,0 };
		dynamicEntity.coll->contactNormal = { 0,0 };

    // Cache division
		FVmath::Point2D invertedDirection = {(1.0f/rayDirection.x),(1.0f/rayDirection.y)};

    FVmath::Point2D nearHit = (target.pos-rayOrigin)*invertedDirection;
    FVmath::Point2D farHit = (target.pos+target.size-rayOrigin)*invertedDirection;

    //Check if there are 0
    if (std::isnan(farHit.y) || std::isnan(farHit.x)) return false;
		if (std::isnan(nearHit.y) || std::isnan(nearHit.x)) return false;

		// Sort distances
		if (nearHit.x > farHit.x) std::swap(nearHit.x, farHit.x);
		if (nearHit.y > farHit.y) std::swap(nearHit.y, farHit.y);

    // // Early rejection		
		if (nearHit.x > farHit.y || nearHit.y > farHit.x) return false;

    // Closest 'time' will be the first contact
		dynamicEntity.coll->contactTime = std::max(nearHit.x, nearHit.y);

		// Furthest 'time' is contact on opposite side of target
		float farTimehit = std::min(farHit.x, farHit.y);

		// Reject if ray direction is pointing away from object
		if (farTimehit < 0)
			return false;

		//Contact point of collision from parametric line equation, its inverted due to being a noob
		dynamicEntity.coll->contactPoint = (rayDirection * dynamicEntity.coll->contactTime) + rayOrigin  ;

		if (nearHit.x > nearHit.y)
			if (invertedDirection.x < 0)
				dynamicEntity.coll->contactNormal = { 1, 0 };
			else
				dynamicEntity.coll->contactNormal = { -1, 0 };
		else if (nearHit.x < nearHit.y)
    {
			if (invertedDirection.y < 0)
				dynamicEntity.coll->contactNormal = { 0, 1 };
			else
      {
				dynamicEntity.coll->contactNormal = { 0, -1 };
      }
    }


		// Note if nearHit == farHit, collision is principly in a diagonal
		// so pointless to resolve. By returning a CN={0,0} even though its
		// considered a hit, the resolver wont change anything.
		return true;
  }

  bool CollisionSys::DynamicEntityVsStaticEntity(Entity& dynamicEntity, const float dt, Entity& staticEntity)
  {
    // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
    if (dynamicEntity.physics->vel.x == 0 && dynamicEntity.physics->vel.y == 0)
      return false;

    // Expand target rectangle by source dimensions
    expandedTarget expanded_target{};
    expanded_target.pos = staticEntity.physics->pos - dynamicEntity.physics->size / 2;
    expanded_target.size = staticEntity.physics->size + dynamicEntity.physics->size;

    if (rayVsEntity(dynamicEntity.physics->pos + dynamicEntity.physics->size / 2, dynamicEntity.physics->vel * dt, expanded_target,dynamicEntity))
      return (dynamicEntity.coll->contactTime >= 0.0f && dynamicEntity.coll->contactTime < 1.0f);
    else
      return false;
  }

  bool CollisionSys::ResolveDynamicEntityVsEntity(Entity& dynamicEntity, Entity& staticEntity, const float dt)
  {

			if (DynamicEntityVsStaticEntity(dynamicEntity, dt, staticEntity))
			{
				dynamicEntity.physics->vel += dynamicEntity.coll->contactNormal * FVmath::Point2D{std::abs(dynamicEntity.physics->vel.x), std::abs(dynamicEntity.physics->vel.y)} * (1 - dynamicEntity.coll->contactTime);
				return true;
			}

			return false;
  }

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
    sf::Vector2f s2_HalfSize = {sprite2Bbox.height /2.0f , sprite2Bbox.height/ 2.0f};

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
