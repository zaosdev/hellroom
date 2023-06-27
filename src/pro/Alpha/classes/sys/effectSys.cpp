#include "effectSys.hpp"
#include <cassert>
#include <cstddef>




namespace game
{
        
        effctSys::effctSys(FVeng::GameManager& Gman)
        : gMan_(Gman)
        {
        }

        void effctSys::update(float dt)
        {      
            //DEFINE LAMBDAS
                auto hasEffect =  [](game::Entity& e){return e.alive() && e.effct ;};
                auto isApplied = [](game::Entity& e){return  e.effct->state == effectState::applied;};
                auto readyToApplyEffect = [](game::Entity& e){return  e.effct->state == effectState::readyToApply;};
            /////////////////////

            for(auto& e : gMan_.getEntityManager()){

                if(hasEffect(e))
                {
                    if(isApplied(e))
                    {
                        proccesAppliedEffects(e,dt);
                    }
                    if(readyToApplyEffect(e))
                    {  
                        transferEffect(e);
                        //listEffect(effect);
                    }
                    else
                    {
                        listEffect(*e.effct);
                    }  
                }
                

              
                //Create all bullets at the end of the weapon loop
            }
                
        }

        void effctSys::listEffect(EffectComponent& effect)
        {

            for(auto& efct : effect.effects)
            {
                std::cout << "Description" << efct.description << "\n";
            }
            std::cout << "state: " << int(effect.state) << "\n";
            //std::cout << "entityID: " << effect.getEntityID() << "\n";

        }

        void effctSys::setEffectToApply(EffectComponent& efct, int eID)
        {
            assert(efct.state!=effectState::readyToApply && efct.state!=effectState::applied);

            efct.state = effectState::readyToApply;
            efct.affectedPartyID = eID;
        }

        void effctSys::transferEffect(game::Entity& e)
        {
            ///////DEFINE LAMBDAS
                auto isAlive = [](game::Entity* e){return e && e->alive();};
                auto canStack =[](const effect_utils::effectType* effct){ return effct && effct->Flags & effect_utils::effectFlags::canStack ;};
                auto isStacking = [&](std::string name, EffectComponent& affctdParty,effect_utils::effectType* efctStack)
                {
                    auto it =  std::find_if(
                        affctdParty.effects.begin(), 
                        affctdParty.effects.end(), 
                        [&](effect_utils::effectType& efct){return 0 == efct.name.compare(name) ;}
                    );
                    if(it!=affctdParty.effects.end())  
                    {
                        efctStack = it.base();
                        return true;
                    }
                    else    
                        return false;
                };
            /////////////////////

            auto* affectedParty = gMan_.getEntityManager().getEntityByID(size_t(e.effct->affectedPartyID));
            bool canApply{true};
            
            if(isAlive(affectedParty))
            {

                //IF AFFECTED PARTY ALREADY HAS AN EFFECT APPLIED
                if(affectedParty->effct)
                {
                    //AUXILIAR VARIABLE IN CASE EFFECT STACKING OCCURS
                    effect_utils::effectType* tempEffct{nullptr};

                    for(auto& efct : e.effct->effects)
                    {
                        //CHECK IF NEW EFFECT WOULD STACK WITH EFFECT ALREADY APPLIED
                        if(not isStacking(efct.name,*affectedParty->effct,tempEffct))
                        {
                            affectedParty->effct->newEffects.push_back(efct);
                        }
                        //IF IT DOES STACK CHECK IF IT'S ALLOWED
                        else if(canStack(tempEffct))
                        {
                            affectedParty->effct->newEffects.push_back(efct);
                        }
                        //IN CASE IT'S NOT ALLOWED DONT APPLY ANY EFFECT
                        else
                        {
                           affectedParty->effct->newEffects.clear();
                           canApply = false;
                           break; 
                        }
                    }
                }
                else
                {
                    //IF IT'S THE FIRST EFFECT CREATE THE COMPONENT
                    affectedParty->effct = EffectComponent{e.effct->newEffects,e.effct->effects,e.effct->state,e.effct->affectedPartyID};
                }
                
                if(canApply)
                {
                    listEffect(*affectedParty->effct);
                    //APPLY EFFECT ON THE AFFECTED PARTY
                    applyNewEffect(*affectedParty);
                    //DELETE ENTITY THAT ORIGINALLY POSSESED EFFECT
                    e.mark4destruction();
                }


            }


        }

        //THIS EFFECT COMPONENT USSUALLY BELONGS TO THE PLAYER
        void effctSys::applyNewEffect(game::Entity& e)
        {

            for(auto& efct : e.effct->newEffects)
            {

                    for(size_t i=0; i<efct.variable.size(); i++)
                    {
                        float& variable = recoverVariable(e,efct.variable[i]);
                        float value{efct.value[i]};

                        std::cout << "variable before: " << variable << "\n";

                        calculateFinalValue(variable,value,efct);

                        std::cout << "variable after: " << variable << "\n";

                    }

                    e.effct->effects.push_back(efct);
            }

            e.effct->state = effectState::applied;

        }

        void effctSys::removeEffect(game::Entity& e,effect_utils::effectType& effct)
        {

            for(size_t i=0; i<effct.variable.size(); i++)
            {
                float& variable = recoverVariable(e,effct.variable[i]);
                float value{effct.value[i]*-1};

                std::cout << "variable before: " << variable << "\n";
                
                calculateFinalValue(variable,value,effct);

                std::cout << "variable after: " << variable << "\n";
            }

        }


        void effctSys::proccesAppliedEffects(game::Entity& e, float dt)
        {
            //DEFINE LAMBDAS
                auto isEntry = [](effect_utils::effectType& effct){return effct.Flags & effect_utils::effectFlags::isEntry;};
                auto isExpirable = [](effect_utils::effectType& effct){return effct.Flags & effect_utils::effectFlags::isExpirable ;};
                auto isExpired = [](effect_utils::effectType& effct){return  effct.expireTime<=0;};
                //auto isTick = [](effect_utils::effectType& effct){return effct.Flags & effect_utils::effectFlags::isTick ;};

            ///////////////////

            std::vector<size_t> effct2Delete{};

            auto& EntityEffects = e.effct->effects;

            for(size_t i{0}; i< EntityEffects.size(); i++)
            {
                auto& efct = EntityEffects[i];

                if(isEntry(efct))
                {
                    effct2Delete.push_back(i);
                }
                else if(isExpirable(efct))
                {
                    if(isExpired(efct))
                    {
                        effct2Delete.push_back(i);
                        removeEffect(e,efct);

                    }
                    else
                    {
                        efct.expireTime-=dt;
                    }
                }
                // else if(isTick(efct))
                // {}
            }

            for(auto& idx : effct2Delete)
            {
                EntityEffects.erase(EntityEffects.begin()+idx);
            }
        }


        void effctSys::calculateFinalValue(float& variable,float& value,effect_utils::effectType& effct)
        {
            //DEFINE LAMBDAS
                auto isPercentage = [](effect_utils::effectType& effct){return effct.Flags & effect_utils::effectFlags::isPercentage;};
                auto isBeneficial = [](effect_utils::effectType& effct){return effct.Flags & effect_utils::effectFlags::isBeneficial;};
            ////////////////

            if(not isBeneficial(effct)){ value*=-1; }

            if(isPercentage(effct)){value = variable*(value/100);}

            variable += value;
        }

        // WeaponComponent& recoverWeaponFromOwner(EffectComponent& efctCmp)
        // {
        //     for(auto& wponCmp : EM_.getComponentVector<WeaponComponent>())
        //     {
        //         if(wponCmp.OwnerID == efctCmp.getEntityID()) return wponCmp;
        //     }

        // }


        //MUST MODIFY THIS SO THAT EFFECTS CAN BE EASILY REMOVED, COMMENTED UNTIL THEN
        float& effctSys::recoverVariable(game::Entity& e,std::string& variableName)
        {

            // if(0==variableName.compare(effect_utils::varCadence))
            // {
            //     auto& wponCmp = *EM_.getComponentByEntityID<WeaponHolderComponent>(efctCmp.getEntityID());

            //    return wponCmp.cadence;
            // }
            // else if(0==variableName.compare(effect_utils::varDamage))
            // {
            //     auto& wponCmp = *EM_.getComponentByEntityID<WeaponHolderComponent>(efctCmp.getEntityID());

            //     return wponCmp.currentWeapon;
            // }
            if(0==variableName.compare(effect_utils::varhealth))
            {
                auto& hpCmp = *e.health;

                return hpCmp.positiveAffection;
            }
            // else if(0==variableName.compare(effect_utils::varMaxHealth))
            // {
            //     auto& hpCmp = *EM_.getComponentByEntityID<HealthComponent>(efctCmp.getEntityID());

            //     return hpCmp.max_health;
            // }
            // else if(0==variableName.compare(effect_utils::varMagazine))
            // {
            //     auto& wponCmp = recoverWeaponFromOwner(efctCmp);

            //     return wponCmp.max_charge;
            // }
            // else if(0==variableName.compare(effect_utils::varReload))
            // {
            //     auto& wponCmp = recoverWeaponFromOwner(efctCmp);

            //     return wponCmp.time2charge;
            // }
            // else if(0==variableName.compare(effect_utils::varAmmo))
            // {
            //     auto& wponCmp = recoverWeaponFromOwner(efctCmp);

            //     std::cout << "AMMO: " << wponCmp.ammunition << "\n";

            //     return wponCmp.ammunition;
            // }
        }


} // Purple Engine
