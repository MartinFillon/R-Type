/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** destroyables
*/

#include <nlohmann/json.hpp>

#include "Components/Destroyable.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{
    auto &destroyables = registry.register_component<ecs::component::Destroyable>();

    destroyables[entity.getId()] = ecs::component::Destroyable{component};
}
