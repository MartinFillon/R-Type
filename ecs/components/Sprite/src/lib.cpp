/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Position
*/

#include <nlohmann/json.hpp>

#include "Components/Sprite.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{
    auto &components = registry.register_component<ecs::component::Sprite>();

    components[entity.getId()] = ecs::component::Sprite{component};
}
