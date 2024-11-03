/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Position
*/

#include <nlohmann/json.hpp>

#include "Components/Rotate.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &position = registry->register_component<ecs::component::Rotate>();

    int pitch = component["pitch"];
    int yaw = component["yaw"];
    int roll = component["roll"];
    position[entity.getId()] = {pitch, yaw, roll};
}
