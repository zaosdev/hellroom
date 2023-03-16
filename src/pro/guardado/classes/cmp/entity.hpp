#pragma once
#include "RenderComponent.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"


#include <optional>

namespace game
{
    struct Entity
    {
      std::optional<RenderComponent> render{};
      std::optional<PhysicsComponent> physics{};
      std::optional<InputComponent> input{};

    };
} // namespace game
