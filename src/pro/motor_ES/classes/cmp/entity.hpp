#pragma once
#include "RenderComponent.hpp"
#include "PhysicsComponent.hpp"

#include <optional>

namespace game
{
    struct Entity
    {
      RenderComponent* render{};
      PhysicsComponent* physics{};

    };
} // namespace game
