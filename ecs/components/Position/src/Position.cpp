/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Position
*/

#include <nlohmann/json.hpp>

#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{
    auto &position = registry.register_component<ecs::component::Position>();

    int x = component["x"];
    int y = component["y"];
    position[entity.getId()] = {x, y};
}
