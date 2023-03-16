#pragma once
#include <vector>

namespace FVeng
{
    template <typename Entity_type>
    struct EntityManager
    {
        using entity_id_type = typename Entity_type::id_type;

        explicit EntityManager(const size_t num_entities = 10)
        {
            entities_.reserve(num_entities);
        }

        EntityManager (const EntityManager&) = delete;
        EntityManager (EntityManager&&) = delete;
        EntityManager& operator=(const EntityManager&)= delete;
        EntityManager& operator=(EntityManager&&)= delete;     

        //Create entity and add it new ID
        [[nodiscard]] Entity_type& createEntity() noexcept { 
            auto& e = new_entities_.emplace_back(Entity_type());
            e.id( ++nextID_ );
            return e;
        }

        //Update entities so that new entities are correctly added to the game
        void update()
        {
            destroyDeadEntities();
            addNewEntities();
        }


        auto begin() noexcept {return entities_.begin();}

        auto end() noexcept {return entities_.end();}

        private:


            //Transfer new entities so that they are affected by the game loop
            void addNewEntities()
            {
                for(auto& e : new_entities_)
                {
                    //use std::move in case entities is not copiable
                    entities_.push_back(std::move(e));
                }
                new_entities_.clear();
            }

            void destroyDeadEntities() noexcept
            {
                //ALmost impossible to happen, just in case
                assert(entities.size() < ((0z-1)/2-1));

                //loop backwards through all the entities on the game, check if they are dead and remove them in case they are
                for(auto i{entities_.size()} ; i!=0; i--)
                {
                    auto& e = entities_[i-1];
                    if(!e.alive())
                    {
                        entities_.erase(entities_.begin()+ long(i-1));
                    }
                }
            }

            //Entities created on current frame that will be added to the game loop on next frame
            std::vector<Entity_type> new_entities_{};
            //Entities that are affected by the game loop
            std::vector<Entity_type> entities_{};
            inline static entity_id_type nextID_ {};
    };
}