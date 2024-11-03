/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** controllables
*/

#include <nlohmann/json.hpp>

#include "Components/RectangleShape.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &rectangle = registry->register_component<ecs::component::RectangleShape>();

    int height = component["height"];
    int width = component["width"];
    int lenght = component["lenght"];

    rectangle[entity.getId()] = {height, width, lenght};
}
