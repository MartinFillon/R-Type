/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** controllables
*/

#include <nlohmann/json.hpp>

#include "Components/Color.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &color = registry->register_component<ecs::component::Color>();

    int r = component["r"];
    int g = component["g"];
    int b = component["b"];
    int a = component["a"];

    color[entity.getId()] = {(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
}
