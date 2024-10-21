/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/Parallax.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{
    auto &components = registry.register_component<ecs::component::Parallax>();

    components[entity.getId()] =
        ecs::component::Parallax{component["active"], component["speed"], component["multiplier"]};
}
