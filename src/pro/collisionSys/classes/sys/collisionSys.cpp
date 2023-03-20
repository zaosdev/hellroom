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


        // auto all_valid = gameMan | filter(isAgent);
        // for(auto& eA : all_valid) {
        //     auto next_valid = gameMan | filter(isBullet);
        //     for(auto& eB : next_valid) {
        //         //are_colliding(eA, eB);
        //     }
        // }


        auto& EM = gameMan.getEntityManager();
        std::vector<int>::iterator it;
        auto valid = [](Entity const& e){
            return e.alive() && e.collider && e.physics;        
        };

        for(auto itA = EM.begin(); itA < EM.end() -1; ++itA){
            if (not valid(*itA)) continue;
            for(auto itB = itA + 1 ; itB < EM.end(); ++itB){
                if(not (valid(*itB))) continue;
            } 
        }
    }
}