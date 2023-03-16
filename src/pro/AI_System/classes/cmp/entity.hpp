#pragma once
#include "RenderComponent.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"
#include "AIComponent.hpp"

#include <optional>

namespace game
{
    struct Entity
    {
      std::optional<RenderComponent>  render{};
      std::optional<PhysicsComponent> physics{};
      std::optional<InputComponent>   input{};
      std::optional<AIComponent>      AI{};
    };
} // namespace game
