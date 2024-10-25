/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/Animations.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &animations = registry->register_component<ecs::component::Animations>();

    animations[entity.getId()] = ecs::component::Animations{
        ecs::Clock(),
        component["width"],
        component["height"],
        component["x"],
        component["y"],
        component["rotation"]
    };
}
