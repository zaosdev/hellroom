#pragma once
#include <vector>

namespace FVeng
{
    template <typename Entity_type>
    struct EntityManager
    {

        explicit EntityManager(const size_t num_entities = 10)
        {
            entities_.reserve(num_entities);
        }//git checkout -b feature/logros

        EntityManager (const EntityManager&) = delete;
        EntityManager (EntityManager&&) = delete;
        EntityManager& operator=(const EntityManager&)= delete;
        EntityManager& operator=(EntityManager&&)= delete;       

        [[nodiscard]] Entity_type& createEntity() noexcept { return entities_.emplace_back();}

        auto begin() noexcept {return entities_.begin();}

        auto end() noexcept {return entities_.end();}

        private:
            std::vector<Entity_type> entities_{};
    };
}