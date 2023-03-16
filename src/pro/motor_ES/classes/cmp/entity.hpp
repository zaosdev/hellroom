#pragma once
#include "RenderComponent.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"


#include <optional>
namespace FVeng { template <typename> struct EntityManager; }

namespace game
{
    struct Entity
    {
      using id_type = uint32_t;

      friend struct FVeng::EntityManager<Entity>;
      
      std::optional<RenderComponent> render{};
      std::optional<PhysicsComponent> physics{};
      std::optional<InputComponent> input{};

      [[nodiscard]] constexpr id_type id() const noexcept { return id_; }
      [[nodiscard]] constexpr bool alive() const noexcept { return alive_; }
      constexpr void     mark4destruction() noexcept { alive_ = false; }

    private:

      [[nodiscard]] explicit Entity() noexcept = default;
      [[maybe_unused]] id_type  id(id_type const i) noexcept { return id_=i; }

      id_type id_{}; 
      bool alive_{true}; 
    };
} // namespace game
