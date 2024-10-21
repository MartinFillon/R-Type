/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/Velocity.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &components = registry->register_component<ecs::component::Velocity>();

    components[entity.getId()] = ecs::component::Velocity{component["x"], component["y"]};
}
