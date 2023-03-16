#pragma once
#include "RenderComponent.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"
#include "AIComponent.hpp"


#include <optional>
namespace FVeng { template <typename> struct EntityManager; }

namespace game
{
    struct Entity
    {
      using id_type = uint32_t;
      using tag_type = id_type;

      enum class TAG : tag_type
      {
        //add new tags when needed and delete placeholder
        placeholerTag,
      };

      friend struct FVeng::EntityManager<Entity>;
      
      std::optional<RenderComponent>  render{};
      std::optional<PhysicsComponent> physics{};
      std::optional<InputComponent>   input{};
      std::optional<AIComponent>      AI{};

      [[nodiscard]] constexpr id_type id() const noexcept { return id_; }
      [[nodiscard]] constexpr bool alive() const noexcept { return alive_; }
      constexpr void mark4destruction() noexcept { alive_ = false; }
      constexpr void addTag(TAG t) noexcept
      {
        tags = tags | tag_type(t); 
      }   
      constexpr tag_type hasTag(TAG t) const noexcept
      {
        return (tags & tag_type(t));
      }

    private:

      [[nodiscard]] explicit Entity() noexcept = default;
      [[maybe_unused]] id_type  id(id_type const i) noexcept { return id_=i; }
      tag_type tags{};
      id_type id_{}; 
      bool alive_{true}; 
    };
} // namespace game