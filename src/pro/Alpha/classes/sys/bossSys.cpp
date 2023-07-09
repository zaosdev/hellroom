#include "bossSys.hpp"


namespace game
{
  BossSys::BossSys(FVeng::GameManager& gameMan/*, SFMLeng::SpriteManager& spriteMan*/)
  : gMan_(gameMan)/*, spriteMan_(spriteMan)*/
  {

  }  

  BossSys::~BossSys() = default;

  void BossSys::update(float dt)
  {
      auto isBoss = [&](game::Entity& e){ return e.hasTag(game::Entity::TAG::BOSS);};
      auto isLaser = [&](game::Entity& e){ return e.hasTag(game::Entity::TAG::LASER);};


      for( auto& e : gMan_.getEntityManager())
      {
          if(isBoss(e))
          {
            if(e.boss->nextState!= boss_state::empty)
                initNewState(e);
            else
            {
                updateCurrentState(e);
            }
          }
          else if(isLaser(e))
          {
            updateLaser(e,dt);
          }
      }
  }


    void BossSys::updateLaser(game::Entity& e,float dt)
    {
        if(e.boss->minDelay2nextState> 0) e.boss->minDelay2nextState-=dt;
        else if(e.boss->currentLaserState == laser_state::charge)
        {
            if(laserSprite_ == 0)
            {
                BossSys::gMan_.initEntityRender(e, {16,16}, SFMLeng::SpriteManager::rect_i_type(32 , 16*laserSprite_, 45, 50));
                e.boss->minDelay2nextState = 0.2f;
                laserSprite_+=6;
            }
            else
            {
                e.boss->currentLaserState = laser_state::attack;
                //gMan_.attackSprite(e);
                e.boss->minDelay2nextState = 0.4f;
            }
        }
        else if(e.boss->currentLaserState == laser_state::attack)
        {
            if(laserSprite_ == 0)
            {
                //BossSys::gMan_.
                e.boss->minDelay2nextState = 0.4f;
            }
            else
            {
                e.mark4destruction();
            }  

        }
    }


    //through the use of idle state decide new state, after ending state change next state to idle otherwise no newstate

  void BossSys::updateCurrentState(game::Entity& e)
  {
    switch (e.boss->nextState)
    {
      case game::boss_state::melee_attack :
      {

        auto bossCenter =  FVmath::Point2D{e.physics->pos.x+e.physics->size.x/2,e.physics->pos.y+e.physics->size.y/2};

        if(FVmath::calculateDistance(gMan_.getPlayer().physics->pos,bossCenter)< 10.0f)
        {
            //play hit animation then create melee hitbox , then revert animation, finally turn to idle state
            e.AI->behaviour = FVAI::SB::STAY;

            e.boss->nextState = boss_state::idle;

            //calculate if player is left or rihgt of the boss

            //create hitbox in correct position

            //play revert animation?

            //if all finished turn to idle state
        }
        else
        {
            e.AI->behaviour = FVAI::SB::PURSUE;
        }

        break;
      }
      case game::boss_state::laser_attack :
      {

        //stop in place and create laser ball, after x time change lase ball size and change it for laser beam
        if(laserId_!= 0)
        {
            e.AI->behaviour = FVAI::SB::STAY;
            auto bossHEAD =  FVmath::Point2Di{int(e.physics->pos.x+e.physics->size.x*0.5),int(e.physics->pos.y+e.physics->size.y*0.15)};

            laserId_ = gMan_.createLaser(bossHEAD).id();
        }

        break;
      }
      case game::boss_state::idle :  
      {
          if(e.health->currentLife > (e.health->maxLife*0.7f))
          {
              e.boss->nextState = boss_state::melee_attack;
          }
          else
          {
              auto rand = FVmath::calculateRandom(100);

              if(rand%2==0)
              {
                e.boss->nextState = boss_state::laser_attack;
              }
              else
              {
                e.boss->nextState = boss_state::melee_attack;
              }

          }
          // call functon 2 decide new state
          break;
      }
      case game::boss_state::empty :            
      default:
      {
          //play idle animation nothing else
          break;
      }

    }

  }


  void BossSys::initNewState(game::Entity& e)
  {
    switch (e.boss->nextState)
    {
      case game::boss_state::dead :
      {
          //stop any behaviour and play death animation
          break;
      }
      case game::boss_state::melee_attack :
      {
        auto bossCenter =  FVmath::Point2D{e.physics->pos.x+e.physics->size.x/2,e.physics->pos.y+e.physics->size.y/2};

        //if in range stop
        if(FVmath::calculateDistance(gMan_.getPlayer().physics->pos,bossCenter)< 10.0f)
        {
            e.AI->behaviour = FVAI::SB::STAY;
        }
        else
        {
            //else pursue player
            e.AI->behaviour = FVAI::SB::PURSUE;
        }

        break;
      }
      case game::boss_state::laser_attack :
      {
        auto bossCenter =  FVmath::Point2D{e.physics->pos.x+e.physics->size.x/2,e.physics->pos.y+e.physics->size.y/2};


        if(FVmath::calculateDistance(gMan_.getPlayer().physics->pos,bossCenter)> 50.0f)
        {
            e.AI->behaviour = FVAI::SB::STAY;
        }
        //stop in place and create laser ball, after x time change lase ball size and change it for laser beam
        

         break;
      }
      case game::boss_state::invincible :
      {
          //stop in place and turn invincible, also play animation
          break;
      }
      case game::boss_state::idle :  
      case game::boss_state::empty :            
      default:
      {
          e.AI->behaviour = FVAI::SB::STAY;
          //play idle animation nothing else
          break;
      }

    }

    e.boss->pastState = e.boss->currentState;
    e.boss->currentState = e.boss->nextState;
    e.boss->nextState = boss_state::empty;

  }


}