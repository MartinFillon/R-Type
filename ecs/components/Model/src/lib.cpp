/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Position
*/

#include <nlohmann/json.hpp>
#include "Components/Model.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &components = registry->register_component<ecs::component::Model>();

    components[entity.getId()] = ecs::component::Model{component};
}
