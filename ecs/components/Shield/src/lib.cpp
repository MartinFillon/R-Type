/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/Shield.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern "C" void register_component(
    std::shared_ptr<ecs::Registry> &registry,
    ecs::Entity &entity,
    const nlohmann::json &component
)
{
    auto &components = registry->register_component<ecs::component::Shield>();

    components[entity.getId()] = ecs::component::Shield{component};
}
