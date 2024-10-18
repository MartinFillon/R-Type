/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** animations
*/

#include <nlohmann/json.hpp>

#include "Components/Animations.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{
    auto &animations = registry.register_component<ecs::component::Animations>();

    ecs::component::Object type = ecs::component::Background;
    ecs::component::Type ennemiesType = ecs::component::Type::None;

    if (component["objectType"] == "boss")
        ennemiesType = ecs::component::Type::Boss;
    else if (component["objectType"] == "basic")
        ennemiesType = ecs::component::Type::Basic;
    else if (component["objectType"] == "milepates")
        ennemiesType = ecs::component::Type::Milespates;

    if (component["type"] == "player")
        type = ecs::component::Player;
    else if (component["type"] == "weapon")
        type = ecs::component::Weapon;
    else if (component["type"] == "ennemies")
        type = ecs::component::Ennemies;
    else if (component["type"] == "background")
        type = ecs::component::Background;

    animations[entity.getId()] = ecs::component::Animations{
        ecs::Clock(),
        component["width"],
        component["height"],
        component["x"],
        component["y"],
        component["rotation"],
        type,
        ennemiesType
    };
}
