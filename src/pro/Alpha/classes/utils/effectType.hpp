
#pragma once
#include <string>
#include <vector>

namespace effect_utils 
{
        enum effectFlags
        {
            isPercentage    = 1 << 0, //value will be used as percantage to be applied on variable affected
            isExpirable     = 1 << 1, //This means that the effect will expire after a given time
            isBeneficial    = 1 << 2, //Effect will have a positive effect on the affected
            canStack        = 1 << 3, //effect can stack with same type effects
            isEntry         = 1 << 4, // effect will be applied only once the first time it's detected as applied
            isTick          = 1 << 5, // effect will be applied every given tick, tick time will be determined by the effect
            isPersistent    = 1 << 6, //effecct will be applied every time it's detected as applied, for example a paralysis effect would remove all movement as long as it's applied
            isRemovable     = 1 << 7, //effect can be removed by external means

        };
       
       
        struct effectType
        {
 
            std::string name;
            std::string description;
            std::vector<float> value{};
            std::vector<std::string> variable{};

            int Flags{0};

            float expireTime{0};

        };

        constexpr const char* varhealth = "health";
        //constexpr const char* varBullet = "bullet";
        constexpr const char* varMaxHealth = "maxHealth";
        // constexpr const char* varReload = "reload";
        // constexpr const char* varMagazine = "magazine";
        // constexpr const char* varCadence = "cadence";
        // constexpr const char* varDamage = "damage";
}