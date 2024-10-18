/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/FilledColor.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{
    auto &components = registry.register_component<ecs::component::FilledColor>();

    double r = component["r"];
    double g = component["g"];
    double b = component["b"];
    double a = component["a"];
    components[entity.getId()] = {r, g, b, a};
}
