#include "collisionSys.hpp"
#include "../man/mapManager.hpp"
#include <iostream>

#define defaultDamage 30

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
      std::vector<Entity*> plyrBullets{};
      std::vector<Entity*> enmyBullets{};



      //bool nomore{false};

      Entity& player = gMan_.getPlayer();
      std::vector<std::pair<Entity*, float>> collInstance{};

      /////////////////////////////////////////
      //LAMBDAS
      auto isEnemy = [&](Entity& ent ){return ent.hasTag(game::Entity::TAG::Enemy) && !ent.hasTag(game::Entity::TAG::Bullet);};
      auto isEnemyBullet = [&](Entity& ent ){return ent.hasTag(game::Entity::TAG::Enemy) && ent.hasTag(game::Entity::TAG::Bullet);};
      auto isStaticObject = [&](Entity& ent ){return ent.hasTag(game::Entity::TAG::STATIC_COLL);};
      auto isHealth = [&](Entity& ent ){return ent.hasTag(game::Entity::TAG::Health);};
      auto isDoor = [&](Entity& ent ){return ent.hasTag(game::Entity::TAG::DOOR);};

      
      //function called when user collides with heart
      auto pickHealth= [&](Entity& entColliding,Entity&  entCollided)
      {
        entCollided.effct->affectedPartyID= entColliding.id();
        entCollided.effct->state=effectState::readyToApply;
      };
      //function called when entity is hit by bullet
      auto bulletHit = [&](Entity& entColliding, Entity&  entCollided)
      {
        entColliding.mark4destruction();
        entCollided.health->negativeAffection = defaultDamage;;
      };
      auto changeLevel = [&](Entity& entColliding, Entity&  entCollided)
      {
        (void)entColliding;
        gMan_.change_level=true;
        gMan_.nextLevel = entCollided.map->nextLevel;
      };
      //Function checks if entities are colliding if they are saves collision so that it may be resolved
      //First parameter must be moving entity- the one that collides with
      //second parameter must be static entity- the one that is collided with
      //third prameter is pointer entity storer, in case we want to save pointer moving entity
      auto saveCollisions = [&](Entity& entColliding, Entity&  entCollided, std::vector<Entity*>* storage)
      {
        if(storage)
          storage->push_back(&entColliding);
        if (DynamicEntityVsStaticEntity(entCollided, dt, entColliding))
        {
          collInstance.push_back({ &entColliding, entCollided.coll->contactTime });
          return true;
        }
        else return false;
      };
      //Function checks if entities are colliding if they are calls third parameter as a function that needs 2 entities as parameter
      //First parameter must be moving entity- the one that collides with
      //second parameter must be static entity- the one that is collided with
      //third prameter must be lambda object that needs 2 entities as paramter and only those
      auto actOnCollisions = [&](Entity& entColliding, Entity&  entCollided, auto action)
      {
       if (DynamicEntityVsStaticEntity(entColliding, dt,entCollided ))
        {
          action(entColliding,entCollided);
        }
      };
      //Resolve entity collisions saved on "collInstance", a collision is added every time "saveCollision" is called
      auto resolveEntityCollisions = [&](Entity& ent)
      {
        if(!collInstance.empty())
        {
          // Do the sort
          std::sort(collInstance.begin(), collInstance.end(), [](const std::pair<Entity*, float>& a, const std::pair<Entity*, float>& b)
            {
              return a.second < b.second;
            });

          for (auto j : collInstance)
          {
            ResolveDynamicEntityVsEntity(ent,*j.first,dt);
          }
        }
        ent.physics->pos+=ent.physics->vel*dt;
      };
      //////////////////////////////////////////
      


      //Entity and enemy obtention loop
      for(auto& ent : EM)
      {
        //IF NEEDS TO BE MORE EFFICIENT CHANGE TO SWITCH
        if(!ent.hasTag(game::Entity::TAG::Player))
        {
          if(isEnemy(ent))
          {
            saveCollisions(ent,player,&enemies);
          }
          else if(isEnemyBullet(ent))
          {
            saveCollisions(ent,player,&enmyBullets);
          }
          else if(isStaticObject(ent))
          {
            saveCollisions(ent,player,&stat_coll);
          }
          else if(isHealth(ent))
          {
            actOnCollisions(player,ent,pickHealth);
          }
          else if(isDoor(ent))
          {
            actOnCollisions(player,ent,changeLevel);
          }
          //AÑADIR ELSE IF SI HAY MAS TIPOS DE COLISIONES
          // else if()
          // {

          // }

        }
        else if(ent.hasTag(game::Entity::TAG::Bullet))
        {
          plyrBullets.push_back(&ent);
        }

      }

    //////////////////////////////////
    //RESEOLVE ALL COLLISIONS THE PLAYER HAS CAUSED
    resolveEntityCollisions(player);
    // collInstance.clear();

    for(auto* enemy : enemies)
    {
      //ENEMY COLLISION AGAINST WALLS
      for(auto* wallColl : stat_coll)
      {
        saveCollisions(*enemy,*wallColl,nullptr);
      }

      //ENEMY COLLISION AGAINST PLAYER, SHOULD USE A MELEE SYSTEM IN THE FUTURE
      if(saveCollisions(*enemy,player,nullptr))
        player.health->negativeAffection = 1;

      //RESOLVE ALL COLLISIONS THIS ENEMY HAS CAUSED
      resolveEntityCollisions(*enemy);
      collInstance.clear();

    }
    for(auto* bullet  : plyrBullets)
    {
      //COLISION DEL ENEMIGO CON LAS BALAS DEL PLAYER
      for(auto* enemy : enemies)
      {
        actOnCollisions(*bullet,*enemy,bulletHit);
      }
      if(bullet->alive())
        bullet->physics->pos+=bullet->physics->vel*dt;
    } 

    for(auto* enmyBullet : enmyBullets)
    {
      actOnCollisions(*enmyBullet,player,bulletHit);
      
      if(enmyBullet->alive())
        enmyBullet->physics->pos+=enmyBullet->physics->vel*dt;
    }


  }


  bool CollisionSys::checkCollision(Entity& collider1, Entity& collider2)
  {

    auto collidersOverlap = [&](Entity& collider1, Entity& collider2)
    {
      auto rect1Pos = collider1.physics->pos;
      auto rect1BBox = collider1.physics->size;
      // Expand target rectangle by source dimensions
      expandedTarget expanded_target{};
      expanded_target.pos = collider2.physics->pos - collider1.physics->size / 2;
      expanded_target.size = collider2.physics->size + collider1.physics->size;

      return ( rect1Pos.x <= expanded_target.pos.x + expanded_target.size.x &&
      rect1Pos.x + rect1BBox.x >= expanded_target.pos.x &&
      rect1Pos.y <= expanded_target.pos.y + expanded_target.size.y &&
      rect1BBox.y + rect1Pos.y >= expanded_target.pos.y);
    };

    if (collidersOverlap(collider1,collider2)) { return true; }
		else                                       { return false; }
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


		// Note if nearHit == farHit, collision is principaly in a diagonal
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

    FVmath::Point2D ent2POS = ent2.physics->pos;


    sf::Vector2f s1_HalfSize = {sprite1Bbox.height /2.0f , sprite1Bbox.width / 2.0f};
    sf::Vector2f s2_HalfSize = {sprite2Bbox.height /2.0f , sprite2Bbox.height/ 2.0f};

    float deltaX = sprite2POS.x - sprite1POS.x;
    float deltaY = sprite2POS.y - sprite1POS.y;

    float intersectX = std::abs(deltaX) - (s2_HalfSize.x + s1_HalfSize.x);
    float intersectY = std::abs(deltaY) - (s2_HalfSize.y + s1_HalfSize.y);

    playerCollision(intersectX, intersectY, deltaX, deltaY, ent2, ent2POS);
    //shieldCollision(intersectX, intersectY, deltaX, deltaY, ent1, ent2POS, ent2, ent2POS);
    
  }


  void CollisionSys::playerCollision(float intersectX, float intersectY,  float deltaX,  float deltaY, Entity& ent2, FVmath::Point2D ent2POS ){
    
    if(intersectX > intersectY) {

      if(deltaX > 0.0f){

        ent2.physics->pos.x = ent2POS.x + (-intersectX);
        
      }
      else{

        ent2.physics->pos.x = ent2POS.x +  (intersectX );
        
      }
    }
    else{
      if(deltaY > 0.0f){

        ent2.physics->pos.y = ent2POS.y + (-intersectY);
          
      }

      else{
        
        ent2.physics->pos.y = ent2POS.y + (intersectY);

      }
    }
  }     

}
