#include "collisionSys.hpp"
#include <cmp/entity.hpp>
#include <man/GameManager.hpp>

namespace game{
    void CollisionSys::update(FVeng::GameManager& gameMan){

        using std::views::filter;
        using std::views::drop;
        using TAG = Entity::TAG;

        auto valid = [](Entity const& e){ return e.alive() && e.collider && e.physics; };
        auto isBullet = [&](Entity const& e){ return valid(e) && e.hasTag(TAG::Bullet); };
        auto isAgent  = [&](Entity const& e){ return valid(e) && e.hasTag(TAG::Enemy) || e.hasTag(TAG::Player);};


        auto all_valid = gameMan | filter(isAgent);
        for(auto& eA : all_valid) {
            auto next_valid = gameMan | filter(isBullet);
            for(auto& eB : next_valid) {
                std::cout << "are colliding" << std::endl;
                //are_colliding(eA, eB);
            }
        }

    }
}