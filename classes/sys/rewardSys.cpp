
#include "rewardSys.hpp"

namespace game
{
    RewardSys::RewardSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {}

    RewardSys::~RewardSys() = default;

    //run over all the entities, if they are marked to dead, get a reward if they have rewardComponent
    void RewardSys::update()
    {
        auto& EM = gMan_.getEntityManager();

        int accumulatedReward = 0;
        for(auto& ent : EM)
        {
            if(!ent.alive() && ent.reward)
            {
                //Calculate a reward between minimum and maximum
                accumulatedReward += FVmath::calculateRandom(ent.reward->max_reward, ent.reward->min_reward);
            }

        }

        //Add to the player
        auto& playerData     = gMan_.getPlayer().data;
        playerData->coins   += accumulatedReward;
    }

}