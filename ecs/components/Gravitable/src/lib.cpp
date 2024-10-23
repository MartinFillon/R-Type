/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/Gravitable.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &components = registry->register_component<ecs::component::Gravitable>();

    bool value = component["value"];
    int gravityFall = component["gravityFall"];
    bool isJumping = component["is_jumping"];
    bool isFalling = component["is_falling"];
    components[entity.getId()] = {value, gravityFall, isJumping, isFalling};
}
