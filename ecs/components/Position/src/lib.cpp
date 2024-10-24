/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Position
*/

#include <nlohmann/json.hpp>

#include "Components/Position.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &position = registry->register_component<ecs::component::Position>();

    int x = component["x"];
    int y = component["y"];
    position[entity.getId()] = {x, y};
}
