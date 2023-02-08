#pragma once
#include "RenderComponent.hpp"
#include <optional>

namespace game
{
    struct Entity
    {
      RenderComponent* render{};
    };
} // namespace game
