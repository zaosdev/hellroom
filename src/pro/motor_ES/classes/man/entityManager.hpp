#pragma once
#include <vector>

namespace FVeng
{
    template <typename Entity_type>
    struct EntityManager
    {
        [[nodiscard]] Entity_type& createEntity() { return entities_.emplace_back();}

        auto& begin() {return entities_.begin();}

        auto& end() {return entities_.end();}


        private:
            std::vector<Entity_type>& entities_{};
    };
}