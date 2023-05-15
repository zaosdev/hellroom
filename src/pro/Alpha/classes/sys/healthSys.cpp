#include "healthSys.hpp"


namespace game
{
    HealthSys::HealthSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    void HealthSys::applyPositive(std::optional<game::HealthComponent>& hc)
    {
        hc->currentLife += hc->positiveAffection;
    }
    
    void HealthSys::applyBoth(std::optional<game::HealthComponent>& hc)
    {
        hc->currentLife += hc->positiveAffection;
        hc->currentLife -= hc->negativeAffection;

        if(hc->negativeAffection > 0) setInmortality(hc); 
    }

    void HealthSys::setInmortality(std::optional<game::HealthComponent>& hc)
    {
        hc->isInmortal = true;
        hc->timePassed = 0;
    }

    void HealthSys::setMortality(std::optional<game::HealthComponent>& hc)
    {
        hc->isInmortal = false;
    }

    void HealthSys::restartEffects(std::optional<game::HealthComponent>& hc)
    {
        hc->positiveAffection = 0;
        hc->negativeAffection = 0;
    }

    void HealthSys::update(double dt)
    {
        auto& EM = gMan_.getEntityManager();

        for(auto& ent : EM)
        {
            if(ent.health)
            {
                auto& hc = ent.health;

               // hc->negativeAffection = 2;
               // hc->positiveAffection = 1;
                //if inmortality time didnt pass, damage will be discarded, else apply both effects
                if(hc->isInmortal)
                {
                    //std::cout << "is inmortal" << std::endl;
                    hc->timePassed += dt;
                    applyPositive(hc);
                    if(hc->timePassed > hc->inmortalityTime) setMortality(hc);
                }                                             
                else  applyBoth(hc);  //if any negative effect is applied, inmortality will be applied
                
                restartEffects(hc);

                //limit life or set to destruction
                if(hc->currentLife > hc->maxLife) hc->currentLife = hc->maxLife;
                else if (hc->currentLife <= 0)
                {
                    if(ent.hasTag(game::Entity::TAG::Player)) {std::cout << "Player is dead, state machine change to new state" << std::endl;}
                    else {
                        gMan_.createHealth(ent.physics->pos);
                        ent.mark4destruction();
                    }
                }    
            }
        }
    }

}