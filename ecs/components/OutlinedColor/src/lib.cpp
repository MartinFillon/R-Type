/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/OutlinedColor.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &components = registry->register_component<ecs::component::OutlinedColor>();

    double r = component["r"];
    double g = component["g"];
    double b = component["b"];
    double a = component["a"];
    components[entity.getId()] = {r, g, b, a};
}
