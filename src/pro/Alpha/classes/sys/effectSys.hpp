#pragma once

#include "../man/GameManager.hpp"
#include "../utils/random.hpp"
#include "../utils/math.hpp"
#include <unordered_map>
#include <string>



namespace game
{
    struct effctSys
    {
        effctSys(FVeng::GameManager& Gman);
        ~effctSys() = default;

        effctSys (const effctSys&) = delete;
        effctSys (effctSys&&) = delete;
        effctSys& operator=(const effctSys&)= delete;
        effctSys& operator=(effctSys&&)= delete;

        void listEffect(EffectComponent& effect);

        void setEffectToApply(EffectComponent& efct, int eID);
        void transferEffect(game::Entity& e); 
        void applyNewEffect(game::Entity& e);
        void proccesAppliedEffects(game::Entity& e, float dt);
        void removeEffect(game::Entity& e,effect_utils::effectType& effct);
        void calculateFinalValue(float& variable,float& value,effect_utils::effectType& effct);

        float& recoverVariable(game::Entity& e,std::string& variableName);
        void modifyVariableFloat(float& variable, float value);

        void update(float dt);

        private:
            FVeng::GameManager& gMan_;
            std::unordered_map<std::string,float*> variable_map_{};
    };
}