/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** controllables
*/

#include <nlohmann/json.hpp>

#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{
    auto &controllables = registry.register_component<ecs::component::Controllable>();

    bool controllable = component["controllable"];
    double speed = component["speed"];
    controllables[entity.getId()] = {controllable, speed};
}
